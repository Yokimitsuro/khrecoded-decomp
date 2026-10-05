#!/usr/bin/env python3
"""Rank still-unported reference functions by their remaining byte differences."""

import argparse
import json
import re
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "build" / "reference_batch_results.json"
INDEX = ROOT / "build" / "func_index.json"
TRIALS = ROOT / "build" / "reference_trials" / "dsi_1.1"
ARM9 = ROOT / "dsd_extract" / "arm9" / "arm9.bin"
SYMBOLS = ROOT / "config" / "arm9" / "symbols.txt"
ARM9_BASE = 0x02000000


def object_symbol(item: dict) -> tuple[bytes, set[int]]:
    path = TRIALS / f"{item['ordinal']:04d}.o"
    with path.open("rb") as handle:
        elf = ELFFile(handle)
        symbols = elf.get_section_by_name(".symtab")
        symbol = next(
            candidate for candidate in symbols.iter_symbols()
            if candidate.name == item["match"]["source_symbol"]
        )
        section_index = symbol["st_shndx"]
        section = elf.get_section(section_index)
        start = symbol["st_value"]
        size = symbol["st_size"]
        relocations = set()
        for reloc_section in elf.iter_sections():
            if reloc_section["sh_type"] not in ("SHT_REL", "SHT_RELA"):
                continue
            if reloc_section["sh_info"] != section_index:
                continue
            for relocation in reloc_section.iter_relocations():
                offset = relocation["r_offset"] - start
                if 0 <= offset < size:
                    relocations.add(offset)
        return section.data()[start:start + size], relocations


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", type=int, default=50)
    args = parser.parse_args()

    results = json.loads(RESULTS.read_text(encoding="utf-8"))
    index = json.loads(INDEX.read_text(encoding="utf-8"))
    symbols = SYMBOLS.read_text(encoding="utf-8")
    arm9 = ARM9.read_bytes()
    existing_sources = {
        path.stem
        for directory in (ROOT / "src", ROOT / "libs")
        for path in directory.rglob("*.c")
    }
    ranked = []

    for item in results:
        name = item["eu"]["name"]
        if not re.search(rf"^{re.escape(name)} kind:function", symbols, re.MULTILINE):
            continue
        if name in existing_sources:
            continue
        try:
            trial, source_relocs = object_symbol(item)
            function = index[name]
        except (KeyError, StopIteration, FileNotFoundError):
            continue
        size = item["eu"]["size"]
        if len(trial) != size:
            continue
        address = item["eu"]["address"]
        expected = arm9[address - ARM9_BASE:address - ARM9_BASE + size]
        ignored = set()
        for offset in source_relocs:
            ignored.update(range(offset, min(offset + 4, size)))
        for offset, _target in function["relocs"]:
            ignored.update(range(offset, min(offset + 4, size)))
        differing = [
            offset for offset, (left, right) in enumerate(zip(expected, trial))
            if offset not in ignored and left != right
        ]
        unit = 2 if item["eu"]["mode"] == "thumb" else 4
        differing_units = len({offset // unit for offset in differing})
        ranked.append((
            differing_units,
            len(differing),
            size,
            name,
            item["match"].get("name", item["match"]["source_symbol"]),
            item["match"].get("domain", ""),
            len(source_relocs),
            len(function["relocs"]),
        ))

    ranked.sort()
    print(f"ranked {len(ranked)} still-raw reference functions")
    for units, byte_count, size, name, readable, domain, source_rel, eu_rel in ranked[:args.limit]:
        print(
            f"{name} {readable} size={size} diff_units={units} "
            f"diff_bytes={byte_count} relocs={source_rel}/{eu_rel} {domain}"
        )


if __name__ == "__main__":
    main()
