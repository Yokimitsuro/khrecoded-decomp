#!/usr/bin/env python3
"""Import pre-verified, relocation-free reference matches in one batch."""

import argparse
import json
import re
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "build" / "reference_batch_results.json"
INDEX = ROOT / "build" / "func_index.json"
REFERENCE = ROOT / "build" / "reference_ricky"
SYMBOLS = ROOT / "config" / "arm9" / "symbols.txt"
DELINKS = ROOT / "config" / "arm9" / "delinks.txt"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"
TRIALS = ROOT / "build" / "reference_trials" / "dsi_1.1"
ADDRESS_SUFFIX_RE = re.compile(r"_[0-9a-fA-F]{8}$")
SYMBOL_LINE_RE = re.compile(
    r"^(\S+)\s+kind:(?:function|data|bss)(?:\([^)]*\))?\s+"
    r"addr:0x([0-9a-fA-F]+)",
    re.MULTILINE,
)
RELOC_LINE_RE = re.compile(
    r"^from:0x([0-9a-fA-F]+)\s+kind:\S+\s+"
    r"to:0x([0-9a-fA-F]+)\s+module:(\S+)$",
    re.MULTILINE,
)


def current_symbol_index() -> tuple[set[str], dict[int, list[str]]]:
    names = set()
    by_address = {}
    for path in (
        SYMBOLS,
        ROOT / "config" / "arm9" / "itcm" / "symbols.txt",
        ROOT / "config" / "arm9" / "dtcm" / "symbols.txt",
    ):
        for match in SYMBOL_LINE_RE.finditer(path.read_text(encoding="utf-8")):
            name = match.group(1)
            names.add(name)
            by_address.setdefault(int(match.group(2), 16), []).append(name)
    return names, by_address


CURRENT_NAMES, CURRENT_BY_ADDRESS = current_symbol_index()
CURRENT_RELOCS = {
    int(match.group(1), 16): (int(match.group(2), 16), match.group(3))
    for match in RELOC_LINE_RE.finditer(
        (ROOT / "config" / "arm9" / "relocs.txt").read_text(encoding="utf-8")
    )
}


def canonical_target(name: str, from_address: int) -> str:
    relocation = CURRENT_RELOCS.get(from_address)
    if relocation is not None and relocation[1] in ("main", "itcm", "dtcm"):
        target_address = relocation[0]
        choices = CURRENT_BY_ADDRESS.get(target_address, [])
        if not choices and target_address & 1:
            choices = CURRENT_BY_ADDRESS.get(target_address - 1, [])
        if choices:
            return min(
                choices,
                key=lambda value: (
                    value.startswith(("func_", "data_", "bss_")),
                    len(value),
                    value,
                ),
            )
    if name in CURRENT_NAMES:
        return name
    match = re.search(r"_([0-9a-fA-F]{8})$", name)
    if match:
        choices = CURRENT_BY_ADDRESS.get(int(match.group(1), 16), [])
        if choices:
            return min(
                choices,
                key=lambda value: (
                    value.startswith(("func_", "data_", "bss_")),
                    len(value),
                    value,
                ),
            )
    return name


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


def replace_identifiers(source: str, replacements: dict[str, str]) -> str:
    if not replacements:
        return source
    pattern = re.compile(
        r"\b(?:" + "|".join(
            sorted((re.escape(name) for name in replacements), key=len, reverse=True)
        ) + r")\b"
    )
    return pattern.sub(lambda match: replacements[match.group(0)], source)


def relocation_rewrites(item: dict, function: dict) -> dict[str, str]:
    object_path = TRIALS / f"{item['ordinal']:04d}.o"
    if not object_path.exists():
        raise RuntimeError(f"compiled trial missing: {object_path}")

    source_symbol = item["match"]["source_symbol"]
    source_relocs = {}
    with object_path.open("rb") as handle:
        elf = ELFFile(handle)
        symtab = elf.get_section_by_name(".symtab")
        symbol = next(
            (candidate for candidate in symtab.iter_symbols()
             if candidate.name == source_symbol),
            None,
        )
        if symbol is None:
            raise RuntimeError(f"compiled symbol missing: {source_symbol}")
        section_index = symbol["st_shndx"]
        start = symbol["st_value"]
        size = symbol["st_size"]
        for reloc_section in elf.iter_sections():
            if reloc_section["sh_type"] not in ("SHT_REL", "SHT_RELA"):
                continue
            if reloc_section["sh_info"] != section_index:
                continue
            linked_symbols = elf.get_section(reloc_section["sh_link"])
            for relocation in reloc_section.iter_relocations():
                offset = relocation["r_offset"] - start
                if not 0 <= offset < size:
                    continue
                target = linked_symbols.get_symbol(relocation["r_info_sym"]).name
                if offset in source_relocs and source_relocs[offset] != target:
                    raise RuntimeError(
                        f"multiple source relocations at {source_symbol}+0x{offset:x}"
                    )
                source_relocs[offset] = target

    eu_relocs = {int(offset): target for offset, target in function["relocs"]}
    if set(source_relocs) != set(eu_relocs):
        raise RuntimeError(
            f"relocation offsets differ for {item['eu']['name']}: "
            f"source={sorted(source_relocs)} eu={sorted(eu_relocs)}"
        )

    rewrites = {}
    for offset, source_name in source_relocs.items():
        target_name = canonical_target(
            eu_relocs[offset], item["eu"]["address"] + offset
        )
        previous = rewrites.setdefault(source_name, target_name)
        if previous != target_name:
            raise RuntimeError(
                f"{source_name} maps to both {previous} and {target_name}"
            )
    return rewrites


def automatic_candidates(results: list[dict], index: dict, symbols: str) -> list[tuple]:
    occupied = set(CURRENT_NAMES)
    candidates = []
    for item in results:
        if item.get("result") != "match":
            continue
        rom_symbol = item["eu"]["name"]
        source_symbol = item["match"]["source_symbol"]
        if source_symbol.startswith(("func_", "FUN_")):
            continue
        if not re.search(
            rf"^{re.escape(rom_symbol)} kind:function", symbols, re.MULTILINE
        ):
            continue
        readable_name = ADDRESS_SUFFIX_RE.sub("", source_symbol)
        if readable_name in occupied:
            readable_name = f"{readable_name}_{item['eu']['address']:08x}"
        if readable_name in occupied:
            continue
        try:
            rewrites = relocation_rewrites(item, index[rom_symbol])
        except (KeyError, RuntimeError):
            continue
        occupied.add(readable_name)
        candidates.append((rom_symbol, readable_name, item, rewrites))
    candidates.sort(key=lambda value: (value[2]["eu"]["size"], value[2]["ordinal"]))
    return candidates


def inferred_name_candidates(results: list[dict], index: dict,
                             symbols: str) -> list[tuple]:
    """Return verified matches whose recovered body still has a generic name.

    These entries were excluded from the original automatic pass because the
    reference function name is address-based. The batch verifier also records
    a reviewed semantic name for some of them, which is safe to use after the
    same relocation checks as the normal import path.
    """
    occupied = set(CURRENT_NAMES)
    candidates = []
    for item in results:
        if item.get("result") != "match":
            continue
        rom_symbol = item["eu"]["name"]
        match = item["match"]
        source_symbol = match["source_symbol"]
        readable_name = ADDRESS_SUFFIX_RE.sub("", match.get("name", ""))
        if not source_symbol.startswith(("func_", "FUN_")):
            continue
        if (not readable_name
                or readable_name.lower() in ("func", "function")
                or readable_name.lower().startswith("unknown")):
            continue
        if readable_name.startswith(("func_", "FUN_")):
            continue
        if not readable_name.isidentifier():
            continue
        if not re.search(
            rf"^{re.escape(rom_symbol)} kind:function", symbols, re.MULTILINE
        ):
            continue
        if readable_name in occupied:
            readable_name = f"{readable_name}_{item['eu']['address']:08x}"
        if readable_name in occupied:
            continue
        try:
            rewrites = relocation_rewrites(item, index[rom_symbol])
        except (KeyError, RuntimeError):
            continue
        occupied.add(readable_name)
        candidates.append((rom_symbol, readable_name, item, rewrites))
    candidates.sort(key=lambda value: (value[2]["eu"]["size"], value[2]["ordinal"]))
    return candidates


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("mapping", nargs="*", type=parse_mapping)
    parser.add_argument("--inventory", action="store_true")
    parser.add_argument("--auto", action="store_true")
    parser.add_argument("--inferred-inventory", action="store_true")
    parser.add_argument("--inferred-auto", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    args = parser.parse_args()

    modes = sum((args.inventory, args.auto, args.inferred_inventory,
                 args.inferred_auto))
    if modes > 1:
        parser.error("select only one automatic or inventory mode")
    if args.mapping and modes:
        parser.error("explicit mappings cannot be combined with --inventory or --auto")
    if not args.mapping and not modes:
        parser.error("provide mappings, --inventory, or --auto")

    result_list = json.loads(RESULTS.read_text(encoding="utf-8"))
    results = {
        item["eu"]["name"]: item
        for item in result_list
        if item.get("result") == "match"
    }
    index = json.loads(INDEX.read_text(encoding="utf-8"))
    symbols = SYMBOLS.read_text(encoding="utf-8")

    cached_rewrites = {}
    if modes:
        if args.inferred_inventory or args.inferred_auto:
            candidates = inferred_name_candidates(result_list, index, symbols)
        else:
            candidates = automatic_candidates(result_list, index, symbols)
        if args.limit:
            candidates = candidates[:args.limit]
        total = sum(item[2]["eu"]["size"] for item in candidates)
        for rom_symbol, readable_name, item, rewrites in candidates:
            print(
                f"{rom_symbol} -> {readable_name} "
                f"({item['eu']['size']} bytes, {len(rewrites)} bindings, "
                f"{item['match']['domain']})"
            )
            cached_rewrites[rom_symbol] = rewrites
        print(f"eligible {len(candidates)} functions, {total} bytes")
        if args.inventory or args.inferred_inventory:
            return
        args.mapping = [(item[0], item[1]) for item in candidates]

    delinks = DELINKS.read_text(encoding="utf-8")
    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))

    imported = []
    renamed_symbols = {}
    for rom_symbol, readable_name in args.mapping:
        if re.search(rf"^{re.escape(readable_name)} kind:function", symbols, re.MULTILINE):
            raise RuntimeError(f"function name already exists: {readable_name}")
        item = results[rom_symbol]
        function = index[rom_symbol]

        match = item["match"]
        reference_symbol = match["source_symbol"]
        reference_path = REFERENCE / match["source"]
        source = reference_path.read_text(encoding="utf-8")
        if reference_symbol not in source:
            raise RuntimeError(f"definition {reference_symbol} not found in {reference_path}")
        rewrites = cached_rewrites.get(rom_symbol)
        if rewrites is None:
            rewrites = relocation_rewrites(item, function)
        rewrites = {**rewrites, reference_symbol: readable_name}
        source = replace_identifiers(source, rewrites)
        source = re.sub(
            r"\.L_([0-9a-fA-F]{8})",
            lambda match: canonical_target(
                match.group(0), int(match.group(1), 16)
            ),
            source,
        )

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
