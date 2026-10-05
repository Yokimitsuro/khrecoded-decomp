#!/usr/bin/env python3
"""Find and import unchanged string DATA from the US reference project.

Only a byte sequence that occurs exactly once in the corresponding European
section is considered. Existing DATA claims and already named symbols are
left untouched. Use --apply to write sources, symbols and delink claims.
"""

import argparse
import ast
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "build" / "reference_ricky"
MANIFEST = REFERENCE / "data_matches.json"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"

DECL_RE = re.compile(
    r'(?:const\s+)?char\s+(\w+)\[(\d+)\]\s*=\s*'
    r'((?:"(?:\\.|[^"\\])*"\s*)+);',
    re.S,
)
LITERAL_RE = re.compile(r'"(?:\\.|[^"\\])*"')
SECTION_RE = re.compile(
    r"^\s+\.(text|rodata|data|ctor|bss)\s+"
    r"start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)"
)
DATA_SYMBOL_RE = re.compile(
    r"^(\S+)(\s+kind:data\([^)]*\)\s+addr:0x([0-9a-fA-F]+).*)$",
    re.MULTILINE,
)
PLACEHOLDER_RE = re.compile(r"^data_(?:ov\d{3}_)?[0-9a-fA-F]{8}$")
IMPORTED_SOURCE_RE = re.compile(
    r"^Strings_(main|ov\d{3})_([0-9a-fA-F]{8})\.c$"
)


def module_paths(module: str) -> tuple[Path, Path]:
    if module == "arm9":
        return ROOT / "config" / "arm9", ROOT / "dsd_extract" / "arm9" / "arm9.bin"
    if module.startswith("ov"):
        return (
            ROOT / "config" / "arm9" / "overlays" / module,
            ROOT / "dsd_extract" / "arm9_overlays" / f"{module}.bin",
        )
    raise ValueError(f"unsupported module: {module}")


def read_module(module: str) -> dict:
    config, binary_path = module_paths(module)
    lines = (config / "delinks.txt").read_text(encoding="utf-8").splitlines()
    sections = {}
    claims = []
    in_header = True
    for line in lines:
        if in_header and not line.strip():
            in_header = False
            continue
        match = SECTION_RE.match(line)
        if not match:
            continue
        section = match.group(1)
        start, end = int(match.group(2), 16), int(match.group(3), 16)
        if in_header:
            sections[section] = (start, end)
        elif section != "text":
            claims.append((section, start, end))
    symbols_path = config / "symbols.txt"
    symbols_text = symbols_path.read_text(encoding="utf-8")
    symbols = {}
    for match in DATA_SYMBOL_RE.finditer(symbols_text):
        # Ambiguous placeholders often point into the middle of a regional
        # string (for example, "s%02d" inside "%s%02d"). Those bytes can be
        # unique without representing a standalone object, so never import
        # them automatically.
        if "ambiguous" not in match.group(2):
            symbols.setdefault(int(match.group(3), 16), []).append(match.group(1))
    return {
        "config": config,
        "binary": binary_path.read_bytes(),
        "base": sections["text"][0],
        "sections": sections,
        "claims": claims,
        "symbols_path": symbols_path,
        "symbols_text": symbols_text,
        "symbols": symbols,
    }


def decode_declarations(source: str, block_start: int) -> list[dict]:
    declarations = []
    for match in DECL_RE.finditer(source):
        old_name, size = match.group(1), int(match.group(2))
        address = int(old_name.rsplit("_", 1)[-1], 16)
        value = "".join(
            ast.literal_eval(item.group(0))
            for item in LITERAL_RE.finditer(match.group(3))
        )
        encoded = value.encode("latin1")
        data = (encoded + b"\0")[:size].ljust(size, b"\0")
        declarations.append({
            "old_name": old_name,
            "offset": address - block_start,
            "size": size,
            "value": value,
            "data": data,
        })
    return declarations


def find_occurrences(data: bytes, needle: bytes, address: int) -> list[int]:
    found = []
    offset = 0
    while True:
        offset = data.find(needle, offset)
        if offset < 0:
            return found
        found.append(address + offset)
        offset += 1


def string_label(value: str) -> str:
    if value == "\n":
        return "Newline"
    replacements = {
        "&": " Language ",
        "%": " Format ",
        "?": " Question ",
        "*": " Star ",
        "#": " Hash ",
    }
    normalized = value
    for old, new in replacements.items():
        normalized = normalized.replace(old, new)
    words = re.findall(r"[A-Za-z0-9]+", normalized)
    if not words:
        return "Empty"
    label = "".join(word[:1].upper() + word[1:] for word in words)
    return label[:72]


def symbol_name(module: str, value: str, address: int) -> str:
    owner = "Main" if module == "arm9" else module[:1].upper() + module[1:]
    return f"s{owner}_{string_label(value)}_{address:08x}"


def source_path(module: str, start: int) -> Path:
    if module == "arm9":
        return ROOT / "src" / "data" / "strings" / f"Strings_main_{start:08x}.c"
    return ROOT / "src" / "overlays" / module / "data" / "strings" / f"Strings_{module}_{start:08x}.c"


def normalize_existing_paths() -> None:
    """Make DATA source basenames unique across modules, as required by dsd."""
    moves = {}
    roots = [("arm9", ROOT / "src" / "data" / "strings")]
    overlays = ROOT / "src" / "overlays"
    if overlays.is_dir():
        roots.extend((path.name, path / "data" / "strings") for path in overlays.iterdir())
    for module, directory in roots:
        if not directory.is_dir():
            continue
        for path in directory.glob("Strings_*.c"):
            if re.match(r"Strings_(?:main|ov\d{3})_[0-9a-f]{8}\.c$", path.name):
                continue
            match = re.match(r"Strings_([0-9a-f]{8})\.c$", path.name)
            if not match:
                continue
            destination = source_path(module, int(match.group(1), 16))
            if destination.exists():
                raise RuntimeError(f"rename destination exists: {destination}")
            old = path.relative_to(ROOT).as_posix()
            path.rename(destination)
            moves[old] = destination.relative_to(ROOT).as_posix()
    if not moves:
        return
    for delinks in (ROOT / "config" / "arm9").glob("**/delinks.txt"):
        text = delinks.read_text(encoding="utf-8")
        updated = text
        for old, new in moves.items():
            updated = updated.replace(old + ":", new + ":")
        if updated != text:
            delinks.write_text(updated, encoding="utf-8", newline="\n")
    compilers = json.loads(COMPILERS.read_text(encoding="utf-8"))
    for old, new in moves.items():
        if old in compilers:
            compilers[new] = compilers.pop(old)
    COMPILERS.write_text(
        json.dumps(compilers, indent=2) + "\n", encoding="utf-8", newline="\n"
    )
    print(f"renamed {len(moves)} DATA sources with module-qualified basenames")


def discover(selected_module: str | None) -> list[dict]:
    entries = json.loads(MANIFEST.read_text(encoding="utf-8"))["data"]
    modules = {}
    candidates = []
    for entry in entries:
        module = entry["module"]
        if entry.get("origin") != "generated strings":
            continue
        if selected_module and module != selected_module:
            continue
        if module != "arm9" and not module.startswith("ov"):
            continue
        info = modules.setdefault(module, read_module(module))
        section = entry["section"].lstrip(".")
        if section not in info["sections"]:
            continue
        us_start, us_end = int(entry["start"], 16), int(entry["end"], 16)
        source = (REFERENCE / entry["source"]).read_text(encoding="utf-8")
        declarations = decode_declarations(source, us_start)
        size = us_end - us_start
        if not declarations or sum(item["size"] for item in declarations) != size:
            continue
        block = bytearray(size)
        valid = True
        for item in declarations:
            offset = item["offset"]
            if offset < 0 or offset + item["size"] > size:
                valid = False
                break
            block[offset:offset + item["size"]] = item["data"]
        if not valid:
            continue
        section_start, section_end = info["sections"][section]
        raw = info["binary"][section_start - info["base"]:section_end - info["base"]]
        occurrences = find_occurrences(raw, bytes(block), section_start)
        if len(occurrences) != 1:
            continue
        eu_start = occurrences[0]
        eu_end = eu_start + size
        if any(section == claimed_section and eu_start < end and start < eu_end
               for claimed_section, start, end in info["claims"]):
            continue
        resolved = []
        for item in declarations:
            address = eu_start + item["offset"]
            names = info["symbols"].get(address, [])
            if len(names) != 1 or not PLACEHOLDER_RE.match(names[0]):
                valid = False
                break
            resolved.append({
                **item,
                "address": address,
                "local_name": names[0],
                "new_name": symbol_name(module, item["value"], address),
            })
        if not valid:
            continue
        candidates.append({
            "module": module,
            "section": section,
            "start": eu_start,
            "end": eu_end,
            "source": source,
            "declarations": resolved,
            "module_info": info,
        })
    return candidates


def replace_symbol(symbols: str, old: str, new: str, address: int) -> str:
    pattern = re.compile(
        rf"^{re.escape(old)}(\s+kind:data\([^)]*\)\s+addr:0x{address:08x}.*)$",
        re.MULTILINE,
    )
    symbols, count = pattern.subn(new + r"\1", symbols)
    if count != 1:
        raise RuntimeError(f"symbol not found once: {old} at 0x{address:08x}")
    return symbols


def placeholder_name(module: str, address: int) -> str:
    if module == "arm9":
        return f"data_{address:08x}"
    return f"data_{module}_{address:08x}"


def imported_sources(module: str) -> list[Path]:
    if module == "arm9":
        directory = ROOT / "src" / "data" / "strings"
    else:
        directory = ROOT / "src" / "overlays" / module / "data" / "strings"
    if not directory.is_dir():
        return []
    return sorted(
        path for path in directory.glob("Strings_*.c")
        if IMPORTED_SOURCE_RE.match(path.name)
    )


def remove_modules(
    modules: list[str],
    selected_starts: dict[str, set[int]] | None = None,
) -> None:
    """Roll back generated string imports for selected modules or blocks."""
    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))
    replacements = {}
    removals = []
    total = 0
    for module in modules:
        info = read_module(module)
        delinks_path = info["config"] / "delinks.txt"
        delinks = delinks_path.read_text(encoding="utf-8")
        symbols = info["symbols_text"]
        for source_path_item in imported_sources(module):
            name_match = IMPORTED_SOURCE_RE.match(source_path_item.name)
            assert name_match is not None
            start = int(name_match.group(2), 16)
            if selected_starts is not None and start not in selected_starts[module]:
                continue
            source = source_path_item.read_text(encoding="utf-8")
            declarations = decode_declarations(source, start)
            if not declarations:
                raise RuntimeError(f"no string declarations in {source_path_item}")
            for declaration in declarations:
                address = start + declaration["offset"]
                semantic = declaration["old_name"]
                placeholder = placeholder_name(module, address)
                symbols = replace_symbol(symbols, semantic, placeholder, address)
                replacements[semantic] = placeholder
                total += declaration["size"]
            relative = source_path_item.relative_to(ROOT).as_posix()
            claim = re.compile(
                rf"^{re.escape(relative)}:\n"
                rf"    complete\n"
                rf"    \.(?:rodata|data)\s+start:0x[0-9a-fA-F]+ "
                rf"end:0x[0-9a-fA-F]+\n?",
                re.MULTILINE,
            )
            delinks, count = claim.subn("", delinks)
            if count != 1:
                raise RuntimeError(f"delink claim not found once: {relative}")
            if relative not in compiler_map:
                raise RuntimeError(f"compiler entry missing: {relative}")
            del compiler_map[relative]
            removals.append(source_path_item)
        info["symbols_path"].write_text(symbols, encoding="utf-8", newline="\n")
        delinks_path.write_text(delinks.rstrip() + "\n", encoding="utf-8", newline="\n")

    replacement_pattern = re.compile(
        r"\b(?:" + "|".join(re.escape(name) for name in replacements) + r")\b"
    ) if replacements else None
    for root in (ROOT / "src", ROOT / "libs"):
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix not in (".c", ".h"):
                continue
            source = path.read_text(encoding="utf-8")
            updated = replacement_pattern.sub(
                lambda match: replacements[match.group(0)], source
            ) if replacement_pattern else source
            if updated != source:
                path.write_text(updated, encoding="utf-8", newline="\n")
    for path in removals:
        path.unlink()
    COMPILERS.write_text(
        json.dumps(compiler_map, indent=2) + "\n", encoding="utf-8", newline="\n"
    )
    print(f"removed {len(removals)} string blocks, {total} bytes from {len(modules)} modules")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--module")
    parser.add_argument("--remove-module", action="append", default=[])
    parser.add_argument(
        "--remove-block",
        action="append",
        default=[],
        metavar="MODULE:ADDRESS",
        help="remove one generated block without touching other module strings",
    )
    args = parser.parse_args()

    if args.remove_block:
        selected_starts = {}
        for spec in args.remove_block:
            try:
                module, address_text = spec.split(":", 1)
                address = int(address_text, 0)
            except ValueError as exc:
                raise SystemExit(f"invalid --remove-block {spec!r}") from exc
            selected_starts.setdefault(module, set()).add(address)
        remove_modules(list(selected_starts), selected_starts)
        return

    if args.remove_module:
        remove_modules(args.remove_module)
        return

    if args.apply:
        normalize_existing_paths()
    candidates = discover(args.module)
    if args.limit:
        candidates = candidates[:args.limit]
    total = sum(item["end"] - item["start"] for item in candidates)
    print(f"eligible {len(candidates)} string blocks, {total} bytes")
    for item in candidates:
        names = ", ".join(entry["new_name"] for entry in item["declarations"])
        print(f"{item['module']} .{item['section']} 0x{item['start']:08x}-0x{item['end']:08x}: {names}")
    if not args.apply:
        return

    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))
    replacements = {}
    touched_modules = {}
    for item in candidates:
        module = item["module"]
        info = item["module_info"]
        touched_modules[module] = info
        source = item["source"]
        for declaration in item["declarations"]:
            source = source.replace(declaration["old_name"], declaration["new_name"])
            info["symbols_text"] = replace_symbol(
                info["symbols_text"], declaration["local_name"], declaration["new_name"],
                declaration["address"],
            )
            replacements[declaration["local_name"]] = declaration["new_name"]
        destination = source_path(module, item["start"])
        destination.parent.mkdir(parents=True, exist_ok=True)
        if destination.exists() and destination.read_text(encoding="utf-8") != source:
            raise RuntimeError(f"destination differs: {destination}")
        destination.write_text(source, encoding="utf-8", newline="\n")
        relative = destination.relative_to(ROOT).as_posix()
        compiler_map[relative] = "dsi/1.1"
        delinks_path = info["config"] / "delinks.txt"
        delinks = delinks_path.read_text(encoding="utf-8").rstrip()
        delinks += (
            f"\n\n{relative}:\n    complete\n"
            f"    .{item['section']:<10} start:0x{item['start']:08x} end:0x{item['end']:08x}\n"
        )
        delinks_path.write_text(delinks, encoding="utf-8", newline="\n")

    for info in touched_modules.values():
        info["symbols_path"].write_text(info["symbols_text"], encoding="utf-8", newline="\n")
    replacement_pattern = re.compile(
        r"\b(?:" + "|".join(re.escape(name) for name in replacements) + r")\b"
    ) if replacements else None
    for root in (ROOT / "src", ROOT / "libs"):
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix not in (".c", ".h"):
                continue
            source = path.read_text(encoding="utf-8")
            updated = replacement_pattern.sub(
                lambda match: replacements[match.group(0)], source
            ) if replacement_pattern else source
            if updated != source:
                path.write_text(updated, encoding="utf-8", newline="\n")
    COMPILERS.write_text(
        json.dumps(compiler_map, indent=2) + "\n", encoding="utf-8", newline="\n"
    )
    print(f"imported {len(candidates)} string blocks, {total} bytes")


if __name__ == "__main__":
    main()
