#!/usr/bin/env python3
"""Disassemble a reference trial beside the corresponding European function."""

import argparse
import json
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_LITTLE_ENDIAN, CS_MODE_THUMB, Cs
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "build" / "reference_batch_results.json"
TRIALS = ROOT / "build" / "reference_trials" / "dsi_1.1"
ARM9 = ROOT / "dsd_extract" / "arm9" / "arm9.bin"
ARM9_BASE = 0x02000000


def object_symbol(path: Path, name: str) -> bytes:
    with path.open("rb") as handle:
        elf = ELFFile(handle)
        symbols = elf.get_section_by_name(".symtab")
        symbol = next(item for item in symbols.iter_symbols() if item.name == name)
        section = elf.get_section(symbol["st_shndx"])
        start = symbol["st_value"]
        return section.data()[start:start + symbol["st_size"]]


def disassemble(data: bytes, address: int, mode: str) -> list[str]:
    cs_mode = CS_MODE_LITTLE_ENDIAN | (CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    decoder = Cs(CS_ARCH_ARM, cs_mode)
    return [
        f"{insn.address:08x}: {insn.bytes.hex():<8} {insn.mnemonic:<8} {insn.op_str}"
        for insn in decoder.disasm(data, address)
    ]


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("symbol")
    parser.add_argument(
        "--built", action="store_true",
        help="compare against the currently linked ARM9 instead of the reference trial",
    )
    parser.add_argument(
        "--object", type=Path,
        help="compare against a freshly compiled ELF object",
    )
    parser.add_argument(
        "--object-symbol",
        help="symbol to extract from --object (defaults to the requested symbol)",
    )
    args = parser.parse_args()
    if args.built and args.object:
        parser.error("--built and --object are mutually exclusive")

    results = json.loads(RESULTS.read_text(encoding="utf-8"))
    item = next(entry for entry in results if entry["eu"]["name"] == args.symbol)
    address = item["eu"]["address"]
    size = item["eu"]["size"]
    mode = item["eu"]["mode"]
    original = ARM9.read_bytes()[address - ARM9_BASE:address - ARM9_BASE + size]
    if args.object:
        trial = object_symbol(args.object, args.object_symbol or args.symbol)
        trial_label = "COMPILED OBJECT"
    elif args.built:
        built = (ROOT / "build" / "build" / "arm9.bin").read_bytes()
        trial = built[address - ARM9_BASE:address - ARM9_BASE + size]
        trial_label = "CURRENT BUILD"
    else:
        trial = object_symbol(
            TRIALS / f"{item['ordinal']:04d}.o", item["match"]["source_symbol"]
        )
        trial_label = "REFERENCE TRIAL"

    expected_lines = disassemble(original, address, mode)
    trial_lines = disassemble(trial, address, mode)
    width = max((len(line) for line in expected_lines), default=0)
    print(f"{args.symbol}: expected {size} bytes, trial {len(trial)} bytes")
    print(f"reference: {item['match']['source']} ({item['match']['source_symbol']})")
    print(f"{'EU ROM':<{width}} | {trial_label}")
    for index in range(max(len(expected_lines), len(trial_lines))):
        left = expected_lines[index] if index < len(expected_lines) else ""
        right = trial_lines[index] if index < len(trial_lines) else ""
        marker = " " if left == right else "!"
        print(f"{left:<{width}} {marker} {right}")


if __name__ == "__main__":
    main()
