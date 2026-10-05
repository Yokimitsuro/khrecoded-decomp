#!/usr/bin/env python3
"""Import exact full-reference matches into their owning EU modules.

Only standalone translation units are considered: the compiled object must
contain exactly the matched text function and no allocatable DATA sections,
and every external relocation must map one-to-one to the EU function index.
This keeps automatic batches reviewable and leaves sources needing companion
headers or DATA for a later structured port.
"""

import argparse
import json
import re
from pathlib import Path

from elftools.elf.elffile import ELFFile

from project import FUNC_INDEX, ROOT


REFERENCE = ROOT / "build" / "reference_ricky"
RESULTS = ROOT / "build" / "reference_full_candidates.json"
OBJECTS = ROOT / "build" / "reference_full_objects"
COMPILERS = ROOT / "config" / "arm9" / "file_compilers.json"

PLACEHOLDER_RE = re.compile(r"^func_(?:ov\d{3}_)?[0-9a-fA-F]{8}$")
INCLUDE_RE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.MULTILINE)
FUNCTION_RE = re.compile(
    r"^(\S+)\s+kind:function\([^\r\n]*\)\s+addr:0x([0-9a-fA-F]+)",
    re.MULTILINE,
)
ADDRESS_SUFFIX_RE = re.compile(r"_[0-9a-fA-F]{8}$")
RAW_SYMBOL_RE = re.compile(
    r"^(?:func|data)_(?:(ov\d{3})_)?([0-9a-fA-F]{8})$"
)
SYMBOL_RE = re.compile(
    r"^(\S+)\s+kind:[^\r\n]+\s+addr:0x([0-9a-fA-F]+)", re.MULTILINE
)
RELOCATION_RE = re.compile(
    r"^from:0x([0-9a-fA-F]+)\s+kind:\S+\s+"
    r"to:0x([0-9a-fA-F]+)\s+module:(\S+)",
    re.MULTILINE,
)
COMPILER_TAG = {
    "mwccarm-4.0-1036": ("dsi_1.1", "dsi/1.1"),
    "mwccarm-3.0-139": ("3.0_patch4", None),
}
KNOWN_SYMBOL_RENAMES = {
    "gCollisionTestSphereDispatch": "gCollisionTestPairDispatch",
    "gCollisionSweepSphereDispatch": "gCollisionSweepPairDispatch",
}


def config_dir(module: str) -> Path:
    if module == "arm9":
        return ROOT / "config" / "arm9"
    if module in ("itcm", "dtcm"):
        return ROOT / "config" / "arm9" / module
    return ROOT / "config" / "arm9" / "overlays" / module


def destination_dir(module: str) -> Path:
    if module.startswith("ov"):
        return ROOT / "src" / "overlays" / module / "calls"
    return ROOT / "src" / "calls"


def object_path(mapping: dict) -> Path:
    tag = COMPILER_TAG[mapping["compiler"]][0]
    return OBJECTS / tag / f"{mapping['reference_index']:05d}.o"


def replace_identifiers(source: str, replacements: dict[str, str]) -> str:
    if not replacements:
        return source
    pattern = re.compile(
        r"\b(?:" + "|".join(
            sorted((re.escape(name) for name in replacements), key=len, reverse=True)
        ) + r")\b"
    )
    return pattern.sub(lambda match: replacements[match.group(0)], source)


def source_with_current_includes(mapping: dict) -> str | None:
    path = REFERENCE / mapping["source"]
    source = path.read_text(encoding="utf-8")
    rewrites = {}
    for include in INCLUDE_RE.findall(source):
        current = include.replace("src/ov", "src/overlays/ov", 1)
        if (ROOT / current).is_file():
            rewrites[include] = current
            continue
        if (ROOT / include).is_file():
            continue
        return None
    for old, new in rewrites.items():
        source = source.replace(f'"{old}"', f'"{new}"')
    return source


def inspect_object(mapping: dict) -> dict | None:
    path = object_path(mapping)
    if not path.exists():
        return None
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return None
        symbols = symtab.get_symbol_by_name(mapping["source_symbol"])
        if not symbols:
            return None
        symbol = next(
            (item for item in symbols if isinstance(item["st_shndx"], int)),
            None,
        )
        if symbol is None:
            return None
        section_index = symbol["st_shndx"]
        section = elf.get_section(section_index)
        if (section.name != ".text" or symbol["st_value"] != 0
                or symbol["st_size"] != mapping["eu"]["size"]
                or section["sh_size"] != symbol["st_size"]):
            return None
        for other in elf.iter_sections():
            if (other.name in (".data", ".rodata", ".ctor")
                    and other["sh_size"]):
                return None

        relocations = {}
        for reloc_section in elf.iter_sections():
            if reloc_section["sh_type"] not in ("SHT_REL", "SHT_RELA"):
                continue
            if reloc_section["sh_info"] != section_index:
                continue
            linked_symbols = elf.get_section(reloc_section["sh_link"])
            for relocation in reloc_section.iter_relocations():
                offset = relocation["r_offset"]
                if not 0 <= offset < symbol["st_size"]:
                    continue
                target = linked_symbols.get_symbol(relocation["r_info_sym"]).name
                previous = relocations.setdefault(offset, target)
                if previous != target:
                    return None
        return {"relocations": relocations}


def useful_name(name: str) -> bool:
    lowered = name.lower()
    return (
        name.isidentifier()
        and not PLACEHOLDER_RE.match(name)
        and not name.startswith(("func_", "FUN_"))
        and lowered not in ("func", "function", "unknown")
        and not lowered.startswith("unknown")
    )


def current_names() -> set[str]:
    names = set()
    for path in (ROOT / "config").glob("**/symbols.txt"):
        for match in FUNCTION_RE.finditer(path.read_text(encoding="utf-8")):
            names.add(match.group(1))
    return names


def current_symbols_by_address() -> dict[tuple[str, int], str]:
    symbols = {}
    directories = [
        ROOT / "config" / "arm9",
        ROOT / "config" / "arm9" / "itcm",
        ROOT / "config" / "arm9" / "dtcm",
        *(ROOT / "config" / "arm9" / "overlays").glob("ov*"),
    ]
    for directory in directories:
        path = directory / "symbols.txt"
        if not path.is_file():
            continue
        module = "main" if directory.name == "arm9" else directory.name
        for match in SYMBOL_RE.finditer(path.read_text(encoding="utf-8")):
            symbols[(module, int(match.group(2), 16))] = match.group(1)
    return symbols


def current_symbol_name(
    name: str,
    symbols: dict[tuple[str, int], str],
    index: dict,
) -> str:
    if name in KNOWN_SYMBOL_RENAMES:
        return KNOWN_SYMBOL_RENAMES[name]
    match = RAW_SYMBOL_RE.match(name)
    if match is None:
        return name
    module = match.group(1) or index.get(name, {}).get("module", "main")
    address = int(match.group(2), 16)
    return symbols.get((module, address), name)


def relocation_target_modules(module: str) -> list[str]:
    match = re.fullmatch(r"overlays\(([\d,]+)\)", module)
    if match:
        return [f"ov{int(number):03d}" for number in match.group(1).split(",")]
    match = re.fullmatch(r"overlay\((\d+)\)", module)
    if match:
        return [f"ov{int(match.group(1)):03d}"]
    return [module]


def current_relocations() -> dict[str, dict[int, tuple[int, str]]]:
    relocations = {}
    directories = [
        ROOT / "config" / "arm9",
        ROOT / "config" / "arm9" / "itcm",
        ROOT / "config" / "arm9" / "dtcm",
        *(ROOT / "config" / "arm9" / "overlays").glob("ov*"),
    ]
    for directory in directories:
        path = directory / "relocs.txt"
        if not path.is_file():
            continue
        module = "main" if directory.name == "arm9" else directory.name
        table = relocations.setdefault(module, {})
        for match in RELOCATION_RE.finditer(path.read_text(encoding="utf-8")):
            table[int(match.group(1), 16)] = (
                int(match.group(2), 16),
                match.group(3),
            )
    return relocations


def relocation_target_name(
    address: int,
    module: str,
    symbols: dict[tuple[str, int], str],
) -> str | None:
    names = {
        symbols[(candidate, target)]
        for candidate in relocation_target_modules(module)
        for target in (address, address & ~1)
        if (candidate, target) in symbols
    }
    if len(names) != 1:
        return None
    return next(iter(names))


def relocation_rewrites(
    mapping: dict,
    object_info: dict,
    index: dict,
    symbols: dict[tuple[str, int], str],
    relocations: dict[str, dict[int, tuple[int, str]]],
) -> dict | None:
    source_relocations = object_info["relocations"]
    module_relocations = relocations.get(mapping["module"], {})
    eu_relocations = {}
    for offset in source_relocations:
        relocation = module_relocations.get(mapping["eu"]["address"] + offset)
        if relocation is None:
            return None
        target_name = relocation_target_name(*relocation, symbols)
        if target_name is None:
            return None
        eu_relocations[offset] = target_name
    expected_offsets = {
        int(offset) for offset, _ in index[mapping["eu"]["name"]]["relocs"]
    }
    if set(source_relocations) != expected_offsets:
        return None
    rewrites = {}
    for offset, source_name in source_relocations.items():
        target_name = eu_relocations[offset]
        if not source_name.isidentifier() or not target_name.isidentifier():
            return None
        previous = rewrites.setdefault(source_name, target_name)
        if previous != target_name:
            return None
    if len(set(rewrites.values())) != len(rewrites):
        return None
    return rewrites


def replace_delink(delinks: str, destination: str, start: int, end: int) -> str:
    range_line = f"    .text       start:0x{start:08x} end:0x{end:08x}"
    if range_line in delinks:
        raise RuntimeError(f"range already claimed: {range_line}")
    return (
        delinks.rstrip()
        + f"\n\n{destination}:\n    complete\n{range_line}\n"
    )


def discover(module: str | None) -> list[dict]:
    index = json.loads(FUNC_INDEX.read_text(encoding="utf-8"))
    mappings = json.loads(RESULTS.read_text(encoding="utf-8"))["mappings"]
    available = current_names()
    occupied = set(available)
    symbols = current_symbols_by_address()
    relocations = current_relocations()
    existing_sources = {
        path.stem
        for top in ("src", "libs")
        for path in (ROOT / top).rglob("*")
        if path.is_file() and path.suffix.lower() in (".c", ".cpp", ".s")
    }
    candidates = []
    for mapping in mappings:
        old_name = mapping["eu"]["name"]
        if module and mapping["module"] != module:
            continue
        if (
            old_name in existing_sources
            or old_name not in available
            or not PLACEHOLDER_RE.match(old_name)
        ):
            continue
        name = mapping["name"]
        if not useful_name(name):
            continue
        source = source_with_current_includes(mapping)
        if source is None:
            continue
        object_info = inspect_object(mapping)
        if object_info is None:
            continue
        rewrites = relocation_rewrites(
            mapping, object_info, index, symbols, relocations
        )
        if rewrites is None:
            continue
        if name in occupied:
            name = f"{name}_{mapping['eu']['address']:08x}"
        if name in occupied:
            continue
        if mapping["source_symbol"] not in source:
            continue
        occupied.add(name)
        candidates.append({
            **mapping,
            "new_name": name,
            "source_text": source,
            "rewrites": rewrites,
        })
    candidates.sort(
        key=lambda item: (
            {"gameplay": 0, "subsystem": 1, "unknown": 2}.get(
                item.get("understanding"), 3
            ),
            item["eu"]["size"],
            item["module"],
            item["eu"]["address"],
        )
    )
    return candidates


def apply(candidates: list[dict]) -> None:
    compiler_map = json.loads(COMPILERS.read_text(encoding="utf-8"))
    modules = {}
    renames = {}
    for item in candidates:
        module = item["module"]
        if module not in modules:
            directory = config_dir(module)
            modules[module] = {
                "symbols_path": directory / "symbols.txt",
                "delinks_path": directory / "delinks.txt",
                "symbols": (directory / "symbols.txt").read_text(encoding="utf-8"),
                "delinks": (directory / "delinks.txt").read_text(encoding="utf-8"),
            }
        state = modules[module]
        old_name = item["eu"]["name"]
        new_name = item["new_name"]
        address = item["eu"]["address"]
        size = item["eu"]["size"]

        rewrites = {**item["rewrites"], item["source_symbol"]: new_name}
        source = replace_identifiers(item["source_text"], rewrites)
        destination = destination_dir(module) / f"{new_name}.c"
        destination.parent.mkdir(parents=True, exist_ok=True)
        if destination.exists():
            raise RuntimeError(f"destination already exists: {destination}")
        destination.write_text(source, encoding="utf-8", newline="\n")

        pattern = re.compile(
            rf"^{re.escape(old_name)}(\s+kind:function\([^\n]+\)\s+"
            rf"addr:0x{address:08x})$",
            re.MULTILINE,
        )
        state["symbols"], count = pattern.subn(new_name + r"\1", state["symbols"])
        if count != 1:
            raise RuntimeError(f"symbol line not found once: {old_name}")

        relative = destination.relative_to(ROOT).as_posix()
        state["delinks"] = replace_delink(
            state["delinks"], relative, address, address + size
        )
        compiler = COMPILER_TAG[item["compiler"]][1]
        if compiler is not None:
            compiler_map[relative] = compiler
        renames[old_name] = new_name

    for state in modules.values():
        state["symbols_path"].write_text(
            state["symbols"], encoding="utf-8", newline="\n"
        )
        state["delinks_path"].write_text(
            state["delinks"], encoding="utf-8", newline="\n"
        )
    COMPILERS.write_text(
        json.dumps(compiler_map, indent=2) + "\n",
        encoding="utf-8",
        newline="\n",
    )

    if renames:
        pattern = re.compile(
            r"\b(?:" + "|".join(
                sorted((re.escape(name) for name in renames), key=len, reverse=True)
            ) + r")\b"
        )
        for top in ("src", "libs"):
            for path in (ROOT / top).rglob("*"):
                if not path.is_file() or path.suffix.lower() not in (".c", ".h"):
                    continue
                source = path.read_text(encoding="utf-8")
                updated = pattern.sub(lambda match: renames[match.group(0)], source)
                if updated != source:
                    path.write_text(updated, encoding="utf-8", newline="\n")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--module")
    parser.add_argument("--max-size", type=lambda value: int(value, 0))
    args = parser.parse_args()

    candidates = discover(args.module)
    if args.max_size is not None:
        candidates = [
            item for item in candidates if item["eu"]["size"] <= args.max_size
        ]
    if args.limit:
        candidates = candidates[:args.limit]
    total = sum(item["eu"]["size"] for item in candidates)
    print(f"eligible {len(candidates)} functions, {total} bytes")
    for item in candidates[:100]:
        print(
            f"{item['module']} {item['eu']['name']} -> {item['new_name']} "
            f"({item['eu']['size']} bytes, {len(item['rewrites'])} bindings)"
        )
    if len(candidates) > 100:
        print(f"... {len(candidates) - 100} more")
    if args.apply:
        apply(candidates)
        print(f"imported {len(candidates)} functions, {total} bytes")


if __name__ == "__main__":
    main()
