#!/usr/bin/env python3
"""Propagate matched C to byte-identical twins inside this ROM.

Two functions whose bytes are identical once the relocated words are masked
are the same code, modulo the symbols they reference. When one of them already
has matching C, the twin's source is that C with every relocated symbol mapped
to the symbol at the twin's relocation target (addends kept) -- the same
mapping tools/port_days.py uses across games. Each written file is verified
with tools/verify_idx.py and removed if it does not match.

    python tools/dedupprop.py            # dry run
    python tools/dedupprop.py --write
"""
import collections
import glob
import json
import os
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, FUNC_INDEX, ROOT  # noqa: E402
from port_days import (ASM_RE, Config, compile_source, index_key, map_symbols,  # noqa: E402
                       masked_key, out_path, port_source, read_object, verify)


def done_sources():
    """function name -> source path of real, matched C (auto/ or calls/)."""
    out = {}
    for top in ("src", "libs"):
        for p in glob.glob(str(ROOT / top / "**" / "*.c"), recursive=True):
            rel = Path(p).relative_to(ROOT).as_posix()
            parts = rel.split("/")
            if "asm_stubs" in parts or "nonmatching" in parts or parts[-2] not in ("auto", "calls"):
                continue
            if ASM_RE.search(Path(p).read_text(encoding="utf-8", errors="replace")):
                continue
            out[Path(p).stem] = rel
    return out


def main():
    write = "--write" in sys.argv
    idx = json.loads(FUNC_INDEX.read_text())
    cfg = Config(ROOT)
    done = done_sources()
    have = {Path(p).stem for top in ("src", "libs")
            for p in glob.glob(str(ROOT / top / "**" / "*.*"), recursive=True)}

    groups = collections.defaultdict(list)
    for name, e in idx.items():
        groups[index_key(e)].append(name)

    work = BUILD_DIR / "dedupprop"
    written = []
    for names in groups.values():
        reps = [n for n in names if n in done]
        todo = [n for n in names if n not in have and n in cfg.sym]
        if not reps or not todo:
            continue
        rep = reps[0]
        mode = idx[rep]["mode"]
        obj = compile_source(ROOT / done[rep], mode, work / (done[rep].replace("/", "__") + ".o"))
        if obj is None:
            continue
        text, relocs, why = read_object(obj, rep)
        if why or masked_key(mode, text, [r[0] for r in relocs]) != index_key(idx[rep]):
            continue
        src = (ROOT / done[rep]).read_text(encoding="utf-8")
        for twin in todo:
            mapping, why = map_symbols(cfg, twin, relocs)
            if mapping is None:
                continue
            mapping[rep] = twin
            path = ROOT / out_path(done[rep], twin, cfg.sym[twin][0], bool(relocs))
            print("  %-32s <- %s" % (twin, rep))
            if write:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(port_source(src, mapping, True, False), encoding="utf-8", newline="\n")
                written.append(path)

    if not write:
        print("dry run; pass --write to apply")
        return
    kept = verify(written, os.cpu_count() or 4)
    for p in written:
        if p not in kept:
            p.unlink()
    print("propagated %d twin(s), %d did not verify" % (len(kept), len(written) - len(kept)))


if __name__ == "__main__":
    main()
