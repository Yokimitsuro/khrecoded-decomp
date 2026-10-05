#!/usr/bin/env python3
"""Recover selected overlay pointer tables using EU relocation metadata."""

import argparse
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "build" / "reference_ricky"
MANIFEST = REFERENCE / "data_matches.json"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"

TABLE_NAMES = {
    ("ov004", 0x02063BE0): "gOv004Callbacks",
    ("ov004", 0x02064520): "gScrollTextHandlers",
    ("ov008", 0x020A13C0): "gOv008ScriptObjectCreationHandlers",
    ("ov009", 0x020A0C40): "gOv009ScriptObjectHandlers",
    ("ov010", 0x020A1D80): "gOv010ScriptObjectCreationHandlers",
    ("ov029", 0x020BAB78): "gOv029SoundControlHandlers",
    ("ov034", 0x020BE924): "gResultsScreenHandlers",
    ("ov035", 0x020BC478): "gMovieSkipHandlers",
    ("ov049", 0x020C46E0): "gCameraMotionInitializers",
    ("ov081", 0x020C5C64): "gBgCharacterLoaders",
    ("ov081", 0x020C5C74): "gBgScreenGetters",
}

SECTION_RE = re.compile(
    r"^\s+\.(text|rodata|data|ctor|bss)\s+"
    r"start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)"
)
TABLE_RE = re.compile(
    r"void\s+\(\*\s*(const\s+)?(\w+)\[(\d+)\]\)\(void\)\s*=\s*"
    r"\{(.*?)\};",
    re.S,
)
RELOC_RE = re.compile(
    r"^from:0x([0-9a-fA-F]+)\s+kind:\S+\s+"
    r"to:0x([0-9a-fA-F]+)\s+module:(\S+)$",
    re.MULTILINE,
)
SYMBOL_RE = re.compile(
    r"^(\S+)\s+kind:(function|data|bss)(?:\(([^)]*)\))?\s+"
    r"addr:0x([0-9a-fA-F]+).*$",
    re.MULTILINE,
)
PLACEHOLDER_RE = re.compile(r"^data_ov\d{3}_[0-9a-fA-F]{8}$")
ADDRESS_SUFFIX_RE = re.compile(r"_[0-9a-fA-F]{8}$")


def module_config(module: str, reference: bool = False) -> Path:
    base = (
        REFERENCE / "config" / "bk9e" / "arm9" / "overlays"
        if reference
        else ROOT / "config" / "arm9" / "overlays"
    )
    return base / module


def layout(path: Path) -> tuple[dict[str, tuple[int, int]], list[tuple[str, int, int]]]:
    sections = {}
    claims = []
    in_header = True
    for line in path.read_text(encoding="utf-8").splitlines():
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
    return sections, claims


def read_symbols(module_name: str) -> dict[int, dict]:
    if module_name == "main":
        path = ROOT / "config" / "arm9" / "symbols.txt"
    elif module_name == "itcm":
        path = ROOT / "config" / "arm9" / "itcm" / "symbols.txt"
    elif module_name == "dtcm":
        path = ROOT / "config" / "arm9" / "dtcm" / "symbols.txt"
    else:
        match = re.fullmatch(r"overlay\((\d+)\)", module_name)
        if not match:
            raise ValueError(f"unknown relocation module: {module_name}")
        overlay = f"ov{int(match.group(1)):03d}"
        path = module_config(overlay) / "symbols.txt"
    result = {}
    for match in SYMBOL_RE.finditer(path.read_text(encoding="utf-8")):
        result.setdefault(int(match.group(4), 16), []).append({
            "name": match.group(1),
            "kind": match.group(2),
            "detail": match.group(3) or "",
        })
    return result


def semantic_name(token: str) -> str:
    token = re.sub(r"^\(void \(\*\)\(void\)\)", "", token)
    return ADDRESS_SUFFIX_RE.sub("", token)


def source_path(module: str, start: int, tables: list[dict]) -> Path:
    filename = (
        f"{tables[0]['name']}.c"
        if len(tables) == 1
        else f"PointerTables_{module}_{start:08x}.c"
    )
    return ROOT / "src" / "overlays" / module / "data" / "tables" / filename


def replace_data_symbol(text: str, old: str, new: str, address: int) -> str:
    pattern = re.compile(
        rf"^{re.escape(old)}(\s+kind:data\([^)]*\)\s+"
        rf"addr:0x{address:08x}.*)$",
        re.MULTILINE,
    )
    text, count = pattern.subn(new + r"\1", text)
    if count != 1:
        raise RuntimeError(f"DATA symbol not found once: {old} at 0x{address:08x}")
    return text


def discover(selected_module: str | None) -> list[dict]:
    entries = json.loads(MANIFEST.read_text(encoding="utf-8"))["data"]
    symbol_cache = {}
    candidates = []
    for entry in entries:
        module = entry["module"]
        if entry.get("origin") != "generated table" or not module.startswith("ov"):
            continue
        if selected_module and module != selected_module:
            continue
        us_start, us_end = int(entry["start"], 16), int(entry["end"], 16)
        source = (REFERENCE / entry["source"]).read_text(encoding="utf-8")
        parsed_tables = TABLE_RE.findall(source)
        table_addresses = [
            int(name.rsplit("_", 1)[-1], 16)
            for _, name, _, _ in parsed_tables
        ]
        if not parsed_tables or any((module, address) not in TABLE_NAMES
                                    for address in table_addresses):
            continue

        config = module_config(module)
        ref_config = module_config(module, reference=True)
        sections, claims = layout(config / "delinks.txt")
        ref_sections, _ = layout(ref_config / "delinks.txt")
        section = entry["section"].lstrip(".")
        eu_start = us_start + sections[section][0] - ref_sections[section][0]
        eu_end = eu_start + us_end - us_start
        module_symbols = symbol_cache.setdefault(
            f"overlay({int(module[2:])})",
            read_symbols(f"overlay({int(module[2:])})"),
        )
        relocations = {
            int(match.group(1), 16): {
                "to": int(match.group(2), 16),
                "module": match.group(3),
            }
            for match in RELOC_RE.finditer(
                (config / "relocs.txt").read_text(encoding="utf-8")
            )
        }
        binary = (
            ROOT / "dsd_extract" / "arm9_overlays" / f"{module}.bin"
        ).read_bytes()
        base = sections["text"][0]

        tables = []
        valid = True
        for is_const, old_table, count_text, body in parsed_tables:
            us_table = int(old_table.rsplit("_", 1)[-1], 16)
            address = eu_start + us_table - us_start
            items = [item.strip() for item in body.split(",") if item.strip()]
            if len(items) != int(count_text):
                valid = False
                break
            resolved = []
            for index, token in enumerate(items):
                from_address = address + index * 4
                raw = struct.unpack_from("<I", binary, from_address - base)[0]
                if token == "NULL":
                    if raw != 0 or from_address in relocations:
                        valid = False
                        break
                    resolved.append(None)
                    continue
                relocation = relocations.get(from_address)
                if relocation is None or raw != relocation["to"]:
                    valid = False
                    break
                targets = symbol_cache.setdefault(
                    relocation["module"], read_symbols(relocation["module"])
                )
                target_address = relocation["to"]
                choices = targets.get(target_address, [])
                if not choices and target_address & 1:
                    choices = targets.get(target_address - 1, [])
                if len(choices) != 1:
                    valid = False
                    break
                target = choices[0]
                semantic = semantic_name(token)
                if semantic in ("func", "data") or semantic.startswith(("func_", "data_")):
                    semantic = target["name"]
                resolved.append({
                    **target,
                    "semantic": semantic,
                })
            if not valid:
                break
            own = module_symbols.get(address, [])
            if len(own) != 1 or not PLACEHOLDER_RE.match(own[0]["name"]):
                valid = False
                break
            tables.append({
                "address": address,
                "old_name": own[0]["name"],
                "name": TABLE_NAMES[(module, us_table)],
                "count": int(count_text),
                "const": bool(is_const),
                "items": resolved,
                "kind": (
                    "function"
                    if all(item is None or item["kind"] == "function" for item in resolved)
                    else "data"
                ),
            })
        if not valid:
            continue

        all_symbol_addresses = sorted(module_symbols)
        last_table_end = max(table["address"] + table["count"] * 4 for table in tables)
        next_symbol = next((value for value in all_symbol_addresses
                            if value >= last_table_end), sections[section][1])
        claim_end = max(eu_end, next_symbol)
        if claim_end > sections[section][1]:
            continue
        padding = binary[eu_end - base:claim_end - base]
        if any(padding):
            continue
        if any(section == claimed_section and eu_start < end and start < claim_end
               for claimed_section, start, end in claims):
            continue
        candidates.append({
            "module": module,
            "config": config,
            "section": section,
            "start": eu_start,
            "end": claim_end,
            "tables": tables,
        })
    return candidates


def render(tables: list[dict]) -> str:
    targets = {}
    for table in tables:
        for item in table["items"]:
            if item is not None:
                targets[item["name"]] = item
    lines = ['#include "nitro/types.h"', ""]
    for name, target in targets.items():
        comment = (
            f" /* {target['semantic']} */"
            if target["semantic"] != name else ""
        )
        if target["kind"] == "function":
            lines.append(f"extern void {name}(void);{comment}")
        else:
            lines.append(f"extern u8 {name}[];{comment}")
    for table in tables:
        declaration = (
            f"void (*{'const ' if table['const'] else ''}{table['name']}"
            f"[{table['count']}])(void)"
            if table["kind"] == "function"
            else f"void *{table['name']}[{table['count']}]"
        )
        lines.extend(["", declaration + " = {"])
        for item in table["items"]:
            if item is None:
                lines.append("    NULL,")
            else:
                comment = (
                    f" /* {item['semantic']} */"
                    if item["semantic"] != item["name"] else ""
                )
                lines.append(f"    {item['name']},{comment}")
        lines.append("};")
    lines.append("")
    return "\n".join(lines)


def apply(candidates: list[dict]) -> None:
    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))
    replacements = {}
    touched = {}
    for candidate in candidates:
        destination = source_path(
            candidate["module"], candidate["start"], candidate["tables"]
        )
        source = render(candidate["tables"])
        destination.parent.mkdir(parents=True, exist_ok=True)
        if destination.exists() and destination.read_text(encoding="utf-8") != source:
            raise RuntimeError(f"destination differs: {destination}")
        destination.write_text(source, encoding="utf-8", newline="\n")
        relative = destination.relative_to(ROOT).as_posix()
        compiler_map[relative] = "dsi/1.1"

        config = candidate["config"]
        state = touched.setdefault(config, {
            "symbols": (config / "symbols.txt").read_text(encoding="utf-8"),
            "delinks": (config / "delinks.txt").read_text(encoding="utf-8").rstrip(),
        })
        for table in candidate["tables"]:
            state["symbols"] = replace_data_symbol(
                state["symbols"], table["old_name"], table["name"], table["address"]
            )
            replacements[table["old_name"]] = table["name"]
        state["delinks"] += (
            f"\n\n{relative}:\n    complete\n"
            f"    .{candidate['section']:<10} start:0x{candidate['start']:08x} "
            f"end:0x{candidate['end']:08x}"
        )

    pattern = re.compile(
        r"\b(?:" + "|".join(re.escape(name) for name in replacements) + r")\b"
    ) if replacements else None
    for root in (ROOT / "src", ROOT / "libs"):
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix not in (".c", ".h"):
                continue
            source = path.read_text(encoding="utf-8")
            updated = pattern.sub(
                lambda match: replacements[match.group(0)], source
            ) if pattern else source
            if updated != source:
                path.write_text(updated, encoding="utf-8", newline="\n")
    for config, state in touched.items():
        (config / "symbols.txt").write_text(
            state["symbols"], encoding="utf-8", newline="\n"
        )
        (config / "delinks.txt").write_text(
            state["delinks"] + "\n", encoding="utf-8", newline="\n"
        )
    COMPILERS.write_text(
        json.dumps(compiler_map, indent=2) + "\n", encoding="utf-8", newline="\n"
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--module")
    args = parser.parse_args()
    candidates = discover(args.module)
    total = sum(item["end"] - item["start"] for item in candidates)
    for candidate in candidates:
        names = ", ".join(table["name"] for table in candidate["tables"])
        print(
            f"{candidate['module']} .{candidate['section']} "
            f"0x{candidate['start']:08x}-0x{candidate['end']:08x}: {names}"
        )
    print(f"eligible {len(candidates)} overlay table blocks, {total} bytes")
    if args.apply:
        apply(candidates)
        print(f"imported {len(candidates)} overlay table blocks, {total} bytes")


if __name__ == "__main__":
    main()
