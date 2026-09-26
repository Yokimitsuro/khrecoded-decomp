#!/usr/bin/env python3
"""Check that every address-named source defines the symbol its file name claims.

A source that defines a function for a different address than its own file
name (for example after propagating a matched file to a twin and rewriting
only part of the name) still verifies under the name it is given, but breaks
the link with one multiply-defined and one undefined symbol. tools/gate.sh runs
this audit before the link.

What it checks, for every source under src/ and libs/, excluding nonmatching/ and asm_stubs/ (the build does not compile
those):

  * if the compiled object exists under build/, the object must export a GLOBAL
    function symbol equal to the file's basename (that is exactly what the
    linker resolves against);
  * otherwise the source text must define a function of that name.

Usage:  python tools/audit_symbol_names.py          # summary, exit 1 on any mismatch
        python tools/audit_symbol_names.py --list   # one line per offending file
"""
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NAME = re.compile(r"^[A-Za-z_]\w*$")
SKIP_DIRS = {"nonmatching", "asm_stubs"}


def source_files():
    for top in ("src", "libs"):
        base = ROOT / top
        if not base.is_dir():
            continue
        for path in base.rglob("*.c"):
            if SKIP_DIRS & set(path.relative_to(ROOT).parts):
                continue
            if NAME.match(path.stem):
                yield path


def object_for(src):
    """The compiled object configure.py/ninja produce for this source, if built."""
    rel = src.relative_to(ROOT).with_suffix(".o")
    obj = ROOT / "build" / rel
    return obj if obj.is_file() else None


def global_functions(obj):
    from elftools.elf.elffile import ELFFile
    with open(obj, "rb") as fh:
        elf = ELFFile(fh)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return set()
        return {
            s.name for s in symtab.iter_symbols()
            if s["st_info"]["type"] == "STT_FUNC"
            and s["st_info"]["bind"] == "STB_GLOBAL"
            and isinstance(s["st_shndx"], int)
        }


def source_defines(src, name):
    text = src.read_text(encoding="utf-8", errors="ignore")
    return re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text) is not None


def main():
    want_list = "--list" in sys.argv
    checked = 0
    bad = []
    for src in sorted(source_files()):
        checked += 1
        name = src.stem
        obj = object_for(src)
        if obj is not None:
            defined = global_functions(obj)
            if name not in defined:
                bad.append((src, "object defines " + (", ".join(sorted(defined)) or "no global function")))
        elif not source_defines(src, name):
            bad.append((src, "source does not define it"))

    if want_list or bad:
        for src, why in bad:
            print("%s: %s" % (src.relative_to(ROOT).as_posix(), why))
    print("audit_symbol_names: %d sources checked, %d whose defined symbol does not match the file name"
          % (checked, len(bad)))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
