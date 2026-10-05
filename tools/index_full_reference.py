#!/usr/bin/env python3
"""Compile and byte-match every verified function from the US reference.

The earlier regional index only covered a small ordinal-aligned subset.  This
tool compiles all verified sources in build/reference_ricky/matches.json and
matches their relocation-masked object code against still-unported EU
functions in the same module.  Repeated bodies are paired by address order
only when both sides contain the same number of functions.
"""

import argparse
import collections
import concurrent.futures as futures
import json
import os
import re
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile

from project import CFLAGS, FUNC_INDEX, LICENSE, MWCCARM, MWCC_DIR, ROOT


REFERENCE = ROOT / "build" / "reference_ricky"
MANIFEST = REFERENCE / "matches.json"
OUTPUT_ROOT = ROOT / "build" / "reference_full_objects"
RESULTS = ROOT / "build" / "reference_full_candidates.json"

FUNCTION_RE = re.compile(
    r"^(\S+)\s+kind:function\((arm|thumb),[^\r\n]*size=0x([0-9a-fA-F]+)"
    r"[^\r\n]*\)\s+addr:0x([0-9a-fA-F]+)",
    re.MULTILINE,
)
PLACEHOLDER_RE = re.compile(r"^func_(?:ov\d{3}_)?[0-9a-fA-F]{8}$")
ADDRESS_SUFFIX_RE = re.compile(r"_[0-9a-fA-F]{8}$")

COMPILERS = {
    "mwccarm-4.0-1036": ("dsi_1.1", MWCC_DIR / "dsi" / "1.1" / "mwccarm.exe"),
    "mwccarm-3.0-139": ("3.0_patch4", MWCCARM),
}


def module_of_symbols(path: Path) -> str:
    text = path.as_posix()
    match = re.search(r"/overlays/(ov\d{3})/", text)
    if match:
        return match.group(1)
    if "/itcm/" in text:
        return "itcm"
    if "/dtcm/" in text:
        return "dtcm"
    return "arm9"


def load_symbols(root: Path) -> dict[tuple[str, str], dict]:
    functions = {}
    for path in (root / "config").glob("**/symbols.txt"):
        module = module_of_symbols(path)
        text = path.read_text(encoding="utf-8", errors="replace")
        for match in FUNCTION_RE.finditer(text):
            name, mode = match.group(1), match.group(2)
            functions[(module, name)] = {
                "module": module,
                "name": name,
                "mode": mode,
                "size": int(match.group(3), 16),
                "address": int(match.group(4), 16),
            }
    return functions


def existing_sources() -> set[str]:
    return {
        path.stem
        for top in ("src", "libs")
        for path in (ROOT / top).rglob("*")
        if path.is_file() and path.suffix.lower() in (".c", ".cpp", ".s")
    }


def compile_one(item: dict, force: bool) -> tuple[dict, str | None]:
    index = item["index"]
    compiler_tag, compiler = COMPILERS[item["compiler"]]
    output_dir = OUTPUT_ROOT / compiler_tag
    output_dir.mkdir(parents=True, exist_ok=True)
    output = output_dir / f"{index:05d}.o"
    if output.exists() and not force:
        return item, None

    flags = list(CFLAGS)
    source = REFERENCE / item["source"]
    if source.suffix.lower() in (".cpp", ".cp", ".cc"):
        flags[flags.index("c99")] = "c++"
    flags.extend(["-i", str(REFERENCE), "-i", str(REFERENCE / "include")])
    if item["mode"] == "thumb":
        flags.append("-thumb")
    command = [str(compiler), "-c", *flags, "-o", str(output), str(source)]
    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    result = subprocess.run(
        command,
        cwd=str(ROOT),
        env=env,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        output.unlink(missing_ok=True)
        lines = (result.stdout + result.stderr).strip().splitlines()
        return item, lines[-1] if lines else "compile failed"
    return item, None


def object_signature(path: Path, symbol_name: str, mode: str) -> tuple | None:
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return None
        symbols = symtab.get_symbol_by_name(symbol_name)
        if not symbols:
            return None
        symbol = next(
            (item for item in symbols if isinstance(item["st_shndx"], int)),
            None,
        )
        if symbol is None or not symbol["st_size"]:
            return None
        section_index = symbol["st_shndx"]
        section = elf.get_section(section_index)
        start = symbol["st_value"]
        size = symbol["st_size"]
        data = bytearray(section.data()[start:start + size])
        relocations = []
        for reloc_section in elf.iter_sections():
            if reloc_section["sh_type"] not in ("SHT_REL", "SHT_RELA"):
                continue
            if reloc_section["sh_info"] != section_index:
                continue
            for relocation in reloc_section.iter_relocations():
                offset = relocation["r_offset"] - start
                if 0 <= offset < size:
                    relocations.append(offset)
        for offset in relocations:
            data[offset:offset + 4] = b"\0\0\0\0"
        return mode, size, bytes(data), tuple(sorted(set(relocations)))


def index_signature(entry: dict) -> tuple:
    data = bytearray.fromhex(entry["hex"])
    offsets = sorted({int(offset) for offset, _ in entry["relocs"]})
    for offset in offsets:
        data[offset:offset + 4] = b"\0\0\0\0"
    return entry["mode"], entry["size"], bytes(data), tuple(offsets)


def readable_name(match: dict) -> str:
    name = match.get("name") or match["source_symbol"]
    if PLACEHOLDER_RE.match(name):
        name = match["source_symbol"]
    return ADDRESS_SUFFIX_RE.sub("", name)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("-j", "--jobs", type=int, default=28)
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()

    reference_symbols = load_symbols(REFERENCE)
    current_symbols = load_symbols(ROOT)
    function_index = json.loads(FUNC_INDEX.read_text(encoding="utf-8"))
    source_names = existing_sources()
    raw_targets = {}
    target_sizes = collections.defaultdict(set)
    for (module, name), symbol in current_symbols.items():
        if not PLACEHOLDER_RE.match(name) or name in source_names:
            continue
        entry = function_index.get(name)
        if entry is None:
            continue
        raw_targets[(module, name)] = {**symbol, "index": entry}
        target_sizes[(module, symbol["mode"])].add(symbol["size"])

    matches = json.loads(MANIFEST.read_text(encoding="utf-8"))["matches"]
    candidates = []
    skipped_manifest = 0
    for index, match in enumerate(matches):
        if match.get("language") not in ("c", "cpp"):
            continue
        compiler = match.get("compiler")
        if compiler not in COMPILERS:
            continue
        ref = reference_symbols.get((match["module"], match["symbol"]))
        if ref is None:
            skipped_manifest += 1
            continue
        if ref["size"] not in target_sizes[(ref["module"], ref["mode"])]:
            continue
        candidates.append({
            "index": index,
            "module": ref["module"],
            "address": ref["address"],
            "size": ref["size"],
            "mode": ref["mode"],
            "compiler": compiler,
            "source": match["source"],
            "source_symbol": match["source_symbol"],
            "symbol": match["symbol"],
            "name": readable_name(match),
            "behavior": match.get("behavior", ""),
            "understanding": match.get("understanding", ""),
        })
    if args.limit:
        candidates = candidates[:args.limit]

    print(
        f"reference candidates={len(candidates)} raw EU targets={len(raw_targets)} "
        f"manifest symbols missing={skipped_manifest}"
    )
    failures = []
    completed = 0
    with futures.ThreadPoolExecutor(max_workers=args.jobs) as executor:
        jobs = [executor.submit(compile_one, item, args.force) for item in candidates]
        for job in futures.as_completed(jobs):
            item, error = job.result()
            completed += 1
            if error:
                failures.append({"index": item["index"], "source": item["source"], "error": error})
            if completed % 500 == 0:
                print(f"  compiled/cached {completed}/{len(candidates)}")

    references_by_key = collections.defaultdict(list)
    for item in candidates:
        compiler_tag = COMPILERS[item["compiler"]][0]
        obj = OUTPUT_ROOT / compiler_tag / f"{item['index']:05d}.o"
        if not obj.exists():
            continue
        signature = object_signature(obj, item["source_symbol"], item["mode"])
        if signature is None or signature[1] != item["size"]:
            continue
        references_by_key[(item["module"], signature)].append(item)

    targets_by_key = collections.defaultdict(list)
    for target in raw_targets.values():
        signature = index_signature(target["index"])
        targets_by_key[(target["module"], signature)].append(target)

    mappings = []
    ambiguous = []
    for key, references in references_by_key.items():
        targets = targets_by_key.get(key, [])
        references.sort(key=lambda item: item["address"])
        targets.sort(key=lambda item: item["address"])
        if not targets:
            continue
        if len(references) != len(targets):
            ambiguous.append({
                "module": key[0],
                "size": key[1][1],
                "references": len(references),
                "targets": len(targets),
                "reference_names": [item["source_symbol"] for item in references],
                "target_names": [item["name"] for item in targets],
            })
            continue
        for reference, target in zip(references, targets):
            mappings.append({
                "module": target["module"],
                "eu": {
                    "name": target["name"],
                    "address": target["address"],
                    "size": target["size"],
                    "mode": target["mode"],
                },
                "us": {
                    "symbol": reference["symbol"],
                    "address": reference["address"],
                },
                "name": reference["name"],
                "source": reference["source"],
                "source_symbol": reference["source_symbol"],
                "reference_index": reference["index"],
                "compiler": reference["compiler"],
                "behavior": reference["behavior"],
                "understanding": reference["understanding"],
            })

    mappings.sort(key=lambda item: (item["module"], item["eu"]["address"]))
    RESULTS.write_text(
        json.dumps({
            "mappings": mappings,
            "ambiguous": ambiguous,
            "compile_failures": failures,
        }, indent=2) + "\n",
        encoding="utf-8",
        newline="\n",
    )
    print(
        f"exact mappings={len(mappings)} ambiguous groups={len(ambiguous)} "
        f"compile failures={len(failures)}"
    )
    for item in mappings[:30]:
        print(
            f"  {item['module']} {item['eu']['name']} -> {item['name']} "
            f"({item['eu']['size']} bytes)"
        )


if __name__ == "__main__":
    main()
