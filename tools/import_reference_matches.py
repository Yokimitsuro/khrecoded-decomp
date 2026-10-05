#!/usr/bin/env python3
"""Import pre-verified, relocation-free reference matches in one batch."""

import argparse
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "build" / "reference_batch_results.json"
INDEX = ROOT / "build" / "func_index.json"
REFERENCE = ROOT / "build" / "reference_ricky"
SYMBOLS = ROOT / "config" / "arm9" / "symbols.txt"
DELINKS = ROOT / "config" / "arm9" / "delinks.txt"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"


def parse_mapping(value: str) -> tuple[str, str]:
    try:
        source, destination = value.split("=", 1)
    except ValueError as error:
        raise argparse.ArgumentTypeError("expected ROM_SYMBOL=READABLE_NAME") from error
    if not source.startswith("func_") or not destination.isidentifier():
        raise argparse.ArgumentTypeError("invalid symbol mapping")
    return source, destination


def replace_delink(delinks: str, old_path: str | None, new_path: str,
                   start: int, end: int) -> str:
    range_line = f"    .text       start:0x{start:08x} end:0x{end:08x}"
    position = delinks.find(range_line)
    if position >= 0:
        header_start = delinks.rfind("\n\n", 0, position) + 2
        header_end = delinks.find(":\n", header_start)
        existing_path = delinks[header_start:header_end]
        if old_path is not None and existing_path != old_path:
            raise RuntimeError(f"unexpected delink owner: {existing_path}")
        return delinks[:header_start] + new_path + delinks[header_end:]
    return delinks.rstrip() + f"\n\n{new_path}:\n    complete\n{range_line}\n"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("mapping", nargs="+", type=parse_mapping)
    args = parser.parse_args()

    results = {
        item["eu"]["name"]: item
        for item in json.loads(RESULTS.read_text(encoding="utf-8"))
        if item.get("result") == "match"
    }
    index = json.loads(INDEX.read_text(encoding="utf-8"))
    symbols = SYMBOLS.read_text(encoding="utf-8")
    delinks = DELINKS.read_text(encoding="utf-8")
    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))

    imported = []
    renamed_symbols = {}
    for rom_symbol, readable_name in args.mapping:
        item = results[rom_symbol]
        function = index[rom_symbol]
        if function["relocs"]:
            raise RuntimeError(f"{rom_symbol} has relocations")

        match = item["match"]
        reference_symbol = match["source_symbol"]
        reference_path = REFERENCE / match["source"]
        source = reference_path.read_text(encoding="utf-8")
        if reference_symbol not in source:
            raise RuntimeError(f"definition {reference_symbol} not found in {reference_path}")
        source = source.replace(reference_symbol, readable_name)

        destination = ROOT / "src" / "calls" / f"{readable_name}.c"
        destination.parent.mkdir(parents=True, exist_ok=True)
        if destination.exists() and destination.read_text(encoding="utf-8") != source:
            raise RuntimeError(f"destination exists with different contents: {destination}")
        destination.write_text(source, encoding="utf-8", newline="\n")

        address = item["eu"]["address"]
        size = item["eu"]["size"]
        symbol_pattern = re.compile(
            rf"^{re.escape(rom_symbol)}( kind:function\([^\n]+\) addr:0x{address:08x})$",
            re.MULTILINE,
        )
        symbols, count = symbol_pattern.subn(readable_name + r"\1", symbols)
        if count != 1:
            raise RuntimeError(f"symbol line not found once: {rom_symbol}")

        range_line = f"    .text       start:0x{address:08x} end:0x{address + size:08x}"
        position = delinks.find(range_line)
        old_path = None
        if position >= 0:
            header_start = delinks.rfind("\n\n", 0, position) + 2
            header_end = delinks.find(":\n", header_start)
            old_path = delinks[header_start:header_end]
        relative_destination = destination.relative_to(ROOT).as_posix()
        delinks = replace_delink(
            delinks, old_path, relative_destination, address, address + size)

        if old_path and old_path != relative_destination:
            old_source = ROOT / old_path
            if old_source.exists():
                old_source.unlink()

        compiler_map[relative_destination] = "dsi/1.1"
        imported.append((rom_symbol, readable_name, size))
        renamed_symbols[rom_symbol] = readable_name

    for source_root in (ROOT / "src", ROOT / "libs"):
        for path in source_root.rglob("*"):
            if not path.is_file() or path.suffix not in (".c", ".h"):
                continue
            source = path.read_text(encoding="utf-8")
            updated = source
            for old_name, new_name in renamed_symbols.items():
                updated = updated.replace(old_name, new_name)
            if updated != source:
                path.write_text(updated, encoding="utf-8", newline="\n")

    SYMBOLS.write_text(symbols, encoding="utf-8", newline="\n")
    DELINKS.write_text(delinks, encoding="utf-8", newline="\n")
    COMPILERS.write_text(
        json.dumps(compiler_map, indent=2) + "\n", encoding="utf-8", newline="\n")

    for rom_symbol, readable_name, size in imported:
        print(f"{rom_symbol} -> {readable_name} ({size} bytes)")
    print(f"imported {len(imported)} functions, {sum(x[2] for x in imported)} bytes")


if __name__ == "__main__":
    main()
