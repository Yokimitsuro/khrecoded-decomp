#!/usr/bin/env python3
"""Compile one C function with mwccarm and compare it byte-for-byte.

Simple mode (no relocations):
    python tools/match.py <file.c> <original_hex> [--thumb]
Reloc-aware mode (functions with calls or data references):
    python tools/match.py <file.c> --obj <delink.o> --func <name> [--thumb]

In reloc-aware mode the relocated words are masked and the relocated symbols
(callees, data) must agree by offset, name and type.

Most day-to-day verification goes through tools/verify_idx.py, which reads the
original bytes from build/func_index.json instead of a delink object.
"""
import os
import subprocess
import sys

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs
from elftools.elf.elffile import ELFFile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from project import BUILD_DIR, CFLAGS, LICENSE, MWCCARM, ROOT  # noqa: E402

ROOT = str(ROOT)


def source_flags(cpath):
    """C99 for .c, C++ for .cpp/.cp/.cc."""
    flags = list(CFLAGS)
    if os.path.splitext(cpath)[1].lower() in (".cpp", ".cp", ".cc"):
        flags[flags.index("c99")] = "c++"
    return flags


def scratch_object(cpath):
    """Object path under build/verify/ for a source, so verification never
    writes objects next to the sources."""
    p = os.path.abspath(cpath)
    try:
        key = os.path.relpath(p, ROOT)
    except ValueError:
        key = p
    key = key.replace(":", "").replace("\\", "/").replace("/", "__").replace("..", "up")
    os.makedirs(os.path.join(str(BUILD_DIR), "verify"), exist_ok=True)
    return os.path.join(str(BUILD_DIR), "verify", key + ".o")


def compile_c(cpath, thumb=False, out=None):
    o = out or scratch_object(cpath)
    if os.path.splitext(cpath)[1].lower() == ".s":
        r = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "_run_armasm.py"), o, cpath],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(r.stdout, r.stderr)
            raise SystemExit("assembly failed")
        return o
    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    flags = source_flags(cpath) + (["-thumb"] if thumb else [])
    r = subprocess.run([str(MWCCARM), "-c", *flags, "-o", o, cpath], capture_output=True, text=True, env=env)
    if r.returncode != 0:
        print(r.stdout, r.stderr)
        raise SystemExit("compilation failed")
    return o


def func_section(elf, name=None):
    """Index of the .text section holding function `name`.

    mwccarm emits every function into its own section, each named `.text`
    with its own `.rela.text`, so the section is selected through the
    function symbol's st_shndx rather than by name.
    """
    if name is None:
        idx = [i for i, s in enumerate(elf.iter_sections()) if s.name == ".text"]
        if len(idx) > 1:
            raise SystemExit("%d .text sections in the object: pass the function name" % len(idx))
        return idx[0] if idx else None
    symtab = elf.get_section_by_name(".symtab")
    for sym in symtab.get_symbol_by_name(name) or []:
        if sym["st_info"]["type"] == "STT_FUNC" and isinstance(sym["st_shndx"], int):
            return sym["st_shndx"]
    raise SystemExit("symbol not found in the object: " + name)


def text_relocs(o_path, name=None):
    """(bytes of the function's .text, {offset: (symbol, reloc type)})."""
    with open(o_path, "rb") as fh:
        elf = ELFFile(fh)
        idx = func_section(elf, name)
        text = elf.get_section(idx).data() if idx is not None else b""
        symtab = elf.get_section_by_name(".symtab")
        rel = {}
        for s in elf.iter_sections():
            if s.name in (".rel.text", ".rela.text") and s["sh_info"] == idx:
                for r in s.iter_relocations():
                    rel[r["r_offset"]] = (symtab.get_symbol(r["r_info_sym"]).name, r["r_info_type"])
    return bytearray(text), rel


def orig_func(delink_o, name):
    with open(delink_o, "rb") as fh:
        elf = ELFFile(fh)
        text = b""
        for s in elf.iter_sections():
            if s.name == ".text":
                text = s.data()
        symtab = elf.get_section_by_name(".symtab")
        val = size = None
        for sym in symtab.iter_symbols():
            if sym.name == name and sym["st_info"]["type"] == "STT_FUNC":
                val = sym["st_value"] & ~1
                size = sym["st_size"]
        if val is None:
            raise SystemExit("symbol not found in delink: " + name)
        fb = bytearray(text[val:val + size])
        rel = {}
        for s in elf.iter_sections():
            if s.name in (".rel.text", ".rela.text"):
                for r in s.iter_relocations():
                    if val <= r["r_offset"] < val + size:
                        rel[r["r_offset"] - val] = (symtab.get_symbol(r["r_info_sym"]).name, r["r_info_type"])
    return fb, rel


def show(code, thumb=False):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    for i in md.disasm(bytes(code), 0):
        print("   %-12s %s" % (" ".join("%02x" % b for b in i.bytes), i.mnemonic + " " + i.op_str))


def cmp_reloc(mine, mrel, orig, orel):
    size = len(orig)
    if len(mine) < size:
        return False, "your function is shorter (%d < %d)" % (len(mine), size)
    mt, ob = bytearray(mine[:size]), bytearray(orig)
    for off in set(mrel) | set(orel):
        for k in range(4):
            if off + k < size:
                mt[off + k] = 0
                ob[off + k] = 0
    if mt != ob:
        d = [i for i in range(size) if mt[i] != ob[i]]
        return False, "byte diff @0x%X (after masking relocs)" % d[0]
    ms = {o: v for o, v in mrel.items() if o < size}
    if ms != orel:
        return False, "relocs differ:\n   yours=%s\n   orig =%s" % (ms, orel)
    return True, "ok"


def main():
    cpath = sys.argv[1]
    thumb = "--thumb" in sys.argv
    o = compile_c(cpath, thumb)
    mine, mrel = text_relocs(o)
    print("=== compiled (.text, %d bytes, %d relocs) ===" % (len(mine), len(mrel)))
    show(mine, thumb)
    if "--obj" in sys.argv:
        delink = sys.argv[sys.argv.index("--obj") + 1]
        name = sys.argv[sys.argv.index("--func") + 1]
        orig, orel = orig_func(delink, name)
        ok, msg = cmp_reloc(mine, mrel, orig, orel)
        print("\norig %d bytes, %d relocs %s" % (len(orig), len(orel), dict(orel)))
        print(">>> MATCH <<<" if ok else ">>> MISMATCH <<< " + msg)
        sys.exit(0 if ok else 1)
    args = [a for a in sys.argv[2:] if not a.startswith("--")]
    if args:
        orig = bytes.fromhex(args[0].replace(" ", ""))
        ok = bytes(mine[:len(orig)]) == orig
        print("orig :", orig.hex())
        print(">>> MATCH <<<" if ok else ">>> MISMATCH <<<")
        sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
