#!/usr/bin/env python3
"""Import simple BSS layouts from the verified US reference project.

The reference manifest contains generated translation units made only of
u8/u16/u32 declarations.  BSS has no bytes to compare, so a candidate is
accepted only when its declarations tile the manifest range exactly, every
translated address has a canonical EU BSS symbol, and the range does not
overlap an existing DATA claim.  The full link gate remains the final proof
that the layout and all references are byte exact.
"""

import argparse
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "build" / "reference_ricky"
MANIFEST = REFERENCE / "data_matches.json"

SECTION_RE = re.compile(
    r"^\s+\.(rodata|data|ctor|bss)\s+"
    r"start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)"
)
SYMBOL_RE = re.compile(
    r"^(\S+)\s+kind:bss\s+addr:0x([0-9a-fA-F]+).*$",
    re.MULTILINE,
)
DECL_RE = re.compile(
    r"^(u8|u16|u32)\s+([A-Za-z_]\w*)"
    r"(?:\[([0-9]+)\])?;\s*$",
    re.MULTILINE,
)
RAW_NAME_RE = re.compile(
    r"^(?:data|bss)_(?:(?:ov\d{3})_)?([0-9a-fA-F]{8})$"
)
PLACEHOLDER_RE = re.compile(
    r"^(?:data|bss)_(?:(?:ov\d{3})_)?[0-9a-fA-F]{8}$"
)
TYPE_SIZE = {"u8": 1, "u16": 2, "u32": 4}
UNSUPPORTED_MODULES = set()


def config_dir(module: str, reference: bool = False) -> Path:
    root = (
        REFERENCE / "config" / "bk9e" / "arm9"
        if reference
        else ROOT / "config" / "arm9"
    )
    if module == "arm9":
        return root
    if module in ("itcm", "dtcm"):
        return root / module
    return root / "overlays" / module


def destination_dir(module: str) -> Path:
    if module == "arm9":
        return ROOT / "src" / "data" / "bss"
    if module in ("itcm", "dtcm"):
        return ROOT / "src" / "data" / module / "bss"
    return ROOT / "src" / "overlays" / module / "data" / "bss"


def section_layout(path: Path) -> tuple[dict[str, tuple[int, int]], list[tuple[str, int, int]]]:
    sections = {}
    claims = []
    in_header = True
    for line in path.read_text(encoding="utf-8").splitlines():
        if in_header and not line.strip():
            in_header = False
            continue
        match = SECTION_RE.match(line)
        if match is None:
            continue
        section = match.group(1)
        start, end = int(match.group(2), 16), int(match.group(3), 16)
        if in_header:
            sections[section] = (start, end)
        else:
            claims.append((section, start, end))
    return sections, claims


def symbols_by_address(path: Path) -> dict[int, list[str]]:
    result = {}
    for match in SYMBOL_RE.finditer(path.read_text(encoding="utf-8")):
        result.setdefault(int(match.group(2), 16), []).append(match.group(1))
    return result


def preferred_name(names: list[str]) -> str | None:
    if not names:
        return None
    semantic = [name for name in names if not PLACEHOLDER_RE.match(name)]
    return (semantic or names)[0]


def reference_symbol_addresses(path: Path) -> dict[str, int]:
    return {
        match.group(1): int(match.group(2), 16)
        for match in SYMBOL_RE.finditer(path.read_text(encoding="utf-8"))
    }


def declaration_address(name: str, reference_symbols: dict[str, int]) -> int | None:
    match = RAW_NAME_RE.match(name)
    if match:
        return int(match.group(1), 16)
    return reference_symbols.get(name)


def replace_identifiers(source: str, replacements: dict[str, str]) -> str:
    if not replacements:
        return source
    pattern = re.compile(
        r"\b(?:" + "|".join(
            sorted((re.escape(name) for name in replacements), key=len, reverse=True)
        ) + r")\b"
    )
    return pattern.sub(lambda match: replacements[match.group(0)], source)


def make_declarations_private(source: str) -> str:
    """Keep layout storage local while references use the canonical symbols.

    Overlay output sections can have a load-address bias caused by their leading
    alignment. Exporting a reconstructed BSS name would override the absolute
    symbol from symbols.txt with that biased link address. Private declarations
    still reconstruct the exact storage layout without changing relocations.
    """
    return re.sub(
        r"^(u8|u16|u32)\s+",
        r"static \1 ",
        source,
        flags=re.MULTILINE,
    )


def discover(selected_module: str | None = None) -> list[dict]:
    entries = json.loads(MANIFEST.read_text(encoding="utf-8"))["data"]
    cache = {}
    candidates = []

    for entry in entries:
        module = entry["module"]
        if entry.get("origin") != "generated layout" or entry["section"] != ".bss":
            continue
        if module in UNSUPPORTED_MODULES:
            continue
        if selected_module and module != selected_module:
            continue

        current_config = config_dir(module)
        reference_config = config_dir(module, reference=True)
        if not current_config.is_dir() or not reference_config.is_dir():
            continue
        current_sections, claims = section_layout(current_config / "delinks.txt")
        reference_sections, _ = section_layout(reference_config / "delinks.txt")
        if "bss" not in current_sections or "bss" not in reference_sections:
            continue

        delta = current_sections["bss"][0] - reference_sections["bss"][0]
        old_start, old_end = int(entry["start"], 16), int(entry["end"], 16)
        start, end = old_start + delta, old_end + delta
        if not (current_sections["bss"][0] <= start < end <= current_sections["bss"][1]):
            continue
        if any(section == "bss" and start < claimed_end and claimed_start < end
               for section, claimed_start, claimed_end in claims):
            continue

        current_symbols = cache.setdefault(
            ("current", module),
            symbols_by_address(current_config / "symbols.txt"),
        )
        reference_symbols = cache.setdefault(
            ("reference", module),
            reference_symbol_addresses(reference_config / "symbols.txt"),
        )
        source_path = REFERENCE / entry["source"]
        source = source_path.read_text(encoding="utf-8")
        declarations = DECL_RE.findall(source)
        if not declarations:
            continue
        stripped = DECL_RE.sub("", source)
        stripped = re.sub(r'^\s*#include\s+"nitro/types.h"\s*$', "", stripped, flags=re.MULTILINE)
        if stripped.strip():
            continue

        chunks = []
        replacements = {}
        valid = True
        for type_name, old_name, count_text in declarations:
            old_address = declaration_address(old_name, reference_symbols)
            if old_address is None:
                valid = False
                break
            address = old_address + delta
            count = int(count_text) if count_text else 1
            size = TYPE_SIZE[type_name] * count
            if not (start <= address and address + size <= end):
                valid = False
                break
            new_name = preferred_name(current_symbols.get(address, []))
            if new_name is None:
                valid = False
                break
            replacements[old_name] = new_name
            chunks.append((address, address + size))
        if not valid:
            continue
        chunks.sort()
        if chunks[0][0] != start or chunks[-1][1] != end:
            continue
        if any(chunks[index][1] != chunks[index + 1][0]
               for index in range(len(chunks) - 1)):
            continue
        # dsd infers a BSS symbol's size from the following symbol. A manifest
        # block ending inside such an inferred range cannot be claimed as a
        # standalone FILE even when the declarations themselves tile it.
        if end != current_sections["bss"][1] and end not in current_symbols:
            continue

        output = make_declarations_private(replace_identifiers(source, replacements))
        prefix = "main" if module == "arm9" else module
        destination = destination_dir(module) / f"Bss_{prefix}_{start:08x}.c"
        if destination.exists():
            continue
        candidates.append({
            "module": module,
            "start": start,
            "end": end,
            "destination": destination,
            "source": output,
            "symbols": len(declarations),
        })

    candidates.sort(key=lambda item: (item["module"], item["start"]))
    return candidates


def apply(candidates: list[dict]) -> None:
    modules = {}
    for item in candidates:
        module = item["module"]
        state = modules.get(module)
        if state is None:
            path = config_dir(module) / "delinks.txt"
            state = modules[module] = {
                "path": path,
                "text": path.read_text(encoding="utf-8").rstrip(),
            }
        destination = item["destination"]
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(item["source"], encoding="utf-8", newline="\n")
        relative = destination.relative_to(ROOT).as_posix()
        state["text"] += (
            f"\n\n{relative}:\n"
            "    complete\n"
            f"    .bss        start:0x{item['start']:08x} end:0x{item['end']:08x}"
        )

    for state in modules.values():
        state["path"].write_text(
            state["text"] + "\n", encoding="utf-8", newline="\n"
        )


def privatize_existing() -> tuple[int, int]:
    files = 0
    declarations = 0
    for path in ROOT.glob("src/**/data/bss/Bss_*.c"):
        source = path.read_text(encoding="utf-8")
        output = make_declarations_private(source)
        if output == source:
            continue
        files += 1
        declarations += len(DECL_RE.findall(source))
        path.write_text(output, encoding="utf-8", newline="\n")
    return files, declarations


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--module")
    parser.add_argument("--privatize-existing", action="store_true")
    args = parser.parse_args()

    if args.privatize_existing:
        files, declarations = privatize_existing()
        print(f"privatized {declarations} declarations in {files} BSS files")
        return

    candidates = discover(args.module)
    if args.limit:
        candidates = candidates[:args.limit]
    total = sum(item["end"] - item["start"] for item in candidates)
    symbols = sum(item["symbols"] for item in candidates)
    print(f"eligible {len(candidates)} BSS blocks, {total} bytes, {symbols} symbols")
    for item in candidates[:80]:
        relative = item["destination"].relative_to(ROOT).as_posix()
        print(
            f"{item['module']} 0x{item['start']:08x}..0x{item['end']:08x} "
            f"{item['symbols']} symbols -> {relative}"
        )
    if len(candidates) > 80:
        print(f"... {len(candidates) - 80} more")
    if args.apply:
        apply(candidates)
        print(f"imported {len(candidates)} BSS blocks, {total} bytes")


if __name__ == "__main__":
    main()
