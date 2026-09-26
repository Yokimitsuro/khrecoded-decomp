#!/usr/bin/env python3
"""Produce the fields of a decomp.me scratch for any function of the ROM.

    python tools/decompme.py <function> [--verify] [--candidate file.c] [--out DIR]

Reads build/func_index.json (hex + relocations + mode), disassembles in the
right mode, resolves the literal pool against the relocations and prints GAS
assembly with labels, which is what decomp.me assembles.

Notes for reading the diff on decomp.me:
  - THUMB->ARM calls are `blx` in the ROM, but mwcc emits `bl` and the project
    fixes interworking after the link (tools/fix_interwork.py), so `bl` is
    emitted here to keep that known difference out of the diff.
  - Pool words carrying a relocation are emitted as `.word <symbol>`; their
    bytes are masked by the verifier, so their value does not matter.

--verify assembles the output with arm-none-eabi-as and compares it with the
ROM bytes; instructions GAS encodes differently from mwcc (e.g. THUMB
`subs rd, rd, #imm`) are rewritten as `.inst`/`.inst.n` with the exact bytes.
--candidate splits an existing C file into decomp.me's context and source.
"""
import json
import os
import shutil
import subprocess
import sys
import tempfile

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from project import CFLAGS, FUNC_INDEX, ROOT  # noqa: E402

FLAGS = " ".join(CFLAGS)
AS_CANDIDATES = [
    "arm-none-eabi-as",
    r"C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\12.2 mpacbti-rel1\bin\arm-none-eabi-as",
]


def symbol_address(name):
    for path in (ROOT / "config").glob("**/symbols.txt"):
        with open(path, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                if line.startswith(name + " "):
                    return int(line.split("addr:0x", 1)[1].split()[0], 16)
    raise SystemExit("not in symbols.txt: " + name)


def verify(out, where, insns, base, data, relocs):
    from match import text_relocs
    asm_exe = next((c for c in AS_CANDIDATES if shutil.which(c) or os.path.exists(c)), None)
    if not asm_exe:
        print("[verify] arm-none-eabi-as not found; skipping")
        return
    by_off = {i.address - base: i for i in insns}
    tmp = tempfile.mkdtemp()
    for _ in range(len(where) + 1):
        s, o = os.path.join(tmp, "t.s"), os.path.join(tmp, "t.o")
        with open(s, "w") as fh:
            fh.write("\n".join(out) + "\n")
        r = subprocess.run([asm_exe, "-mcpu=arm946e-s", "-mthumb-interwork", "-o", o, s],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print("[verify] GAS failed:\n" + r.stderr)
            return
        mine, mrel = text_relocs(o)
        mrel = {k: v[0] for k, v in mrel.items()}
        if mrel != relocs:
            print("[verify] relocations differ\n  mine=%s\n  ROM =%s" % (mrel, relocs))
        a, b = bytearray(mine), bytearray(data)
        if len(a) != len(b):
            print("[verify] size %d != %d" % (len(a), len(b)))
            return
        for off in set(mrel) | set(relocs):
            for k in range(4):
                if off + k < len(b):
                    a[off + k] = b[off + k] = 0
        bad = [i for i in range(len(b)) if a[i] != b[i]]
        if not bad:
            print("[verify] OK: %d bytes identical to the ROM (relocations masked)" % len(b))
            return
        ins = max((i for i in by_off.values() if i.address - base <= bad[0]), key=lambda i: i.address)
        off = ins.address - base
        raw = data[off:off + ins.size]
        directive = (".inst.n 0x%04X" if len(raw) == 2 else ".inst 0x%08X") % int.from_bytes(raw, "little")
        out[where[off]] = "\t%s  @ %s %s" % (directive, ins.mnemonic, ins.op_str)
        print("[verify] different encoding at +0x%02X -> emitted raw (%s %s)" % (off, ins.mnemonic, ins.op_str))
    print("[verify] did not converge; check by hand")


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    name = sys.argv[1]
    idx = json.loads(FUNC_INDEX.read_text())
    if name not in idx:
        raise SystemExit("not in func_index.json: " + name)
    e = idx[name]
    data = bytes.fromhex(e["hex"])
    thumb = e["mode"] == "thumb"
    size = len(data)
    relocs = {off: sym for off, sym in e["relocs"]}
    base = symbol_address(name)

    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
    insns = list(md.disasm(data, base))

    # The pool is derived from the targets of the pc-relative loads, which is
    # exact; pool words also disassemble as valid instructions.
    def pcrel_target(i):
        imm = int(i.op_str.split("#")[1].rstrip("]"), 16)
        return (((i.address + 4) & ~3) if thumb else i.address + 8) + imm - base

    code_end, pool = size, set()
    for i in insns:
        if i.address - base >= code_end:
            break
        if "[pc," in i.op_str:
            t = pcrel_target(i)
            pool.add(t)
            code_end = min(code_end, t)
    pool = [o for o in sorted(pool) if o + 4 <= size]

    targets = set()
    for i in insns:
        if i.address - base < code_end and i.mnemonic.startswith("b") and i.op_str.startswith("#"):
            targets.add(int(i.op_str[1:], 16))

    def lbl(addr):
        return "_%08X" % addr

    out = ["\t.text", "\t.syntax unified", "\t.thumb" if thumb else "\t.arm", "\t.global %s" % name]
    if thumb:
        out.append("\t.thumb_func")
    out.append("%s:" % name)
    where = {}
    for i in insns:
        off = i.address - base
        if off >= code_end:
            break
        if i.address in targets:
            out.append("%s:" % lbl(i.address))
        where[off] = len(out)
        mn, ops = i.mnemonic, i.op_str
        if mn in ("bl", "blx") and ops.startswith("#"):
            out.append("\tbl %s" % relocs.get(off, ops))
        elif mn.startswith("b") and ops.startswith("#"):
            out.append("\t%s %s" % (mn, lbl(int(ops[1:], 16))))
        elif "[pc," in ops:
            pcrel = int(ops.split("#")[1].rstrip("]"), 16)
            src = (i.address + 4) & ~3 if thumb else i.address + 8
            out.append("\t%s %s, %s" % (mn, ops.split(",")[0], lbl(src + pcrel)))
        else:
            out.append("\t%s %s" % (mn, ops))
    out.append("\t.align 2, 0")
    for o in pool:
        val = relocs.get(o) or "0x%08X" % int.from_bytes(data[o:o + 4], "little")
        out.append("%s: .word %s" % (lbl(base + o), val))

    if "--verify" in sys.argv:
        verify(out, where, insns, base, data, relocs)
    asm = "\n".join(out)

    ctx = ["typedef signed char s8;    typedef unsigned char u8;",
           "typedef signed short s16;  typedef unsigned short u16;",
           "typedef signed int s32;    typedef unsigned int u32;",
           "typedef signed long long s64; typedef unsigned long long u64;"]
    for o in pool:
        sym = relocs.get(o)
        if sym:
            ctx.append("extern %s;" % ("void %s()" % sym if sym.startswith("func_") else "char %s[]" % sym))
    for o, sym in relocs.items():
        if o < code_end:
            ctx.append("extern void %s();" % sym)
    context = "\n".join(dict.fromkeys(ctx))

    print("=" * 70)
    print("DECOMP.ME SCRATCH for %s  (%d bytes, %s)" % (name, size, e["mode"]))
    print("=" * 70)
    print("\n[Platform]  Nintendo DS")
    print("[Compiler]  3.0 build 139 (MW 2.0sp2p4)")
    print("\n[Compiler flags]\n" + FLAGS + (" -thumb" if thumb else ""))
    print("\n[Diff label]\n" + name)
    print("\n[Target assembly]\n" + asm)
    print("\n[Context]\n" + context)
    print("\n" + "=" * 70)

    cand_ctx = cand_src = None
    if "--candidate" in sys.argv:
        cpath = sys.argv[sys.argv.index("--candidate") + 1]
        clines = open(cpath, encoding="utf-8").read().split("\n")
        defs = [j for j, x in enumerate(clines)
                if (name + "(") in x and not x.lstrip().startswith("extern") and not x.rstrip().endswith(";")]
        if not defs:
            raise SystemExit("no definition of %s in %s" % (name, cpath))
        start = defs[0]
        while start > 0 and (clines[start - 1].startswith(" *") or clines[start - 1].startswith("/*")):
            start -= 1
        cand_ctx = "\n".join(clines[:start]).rstrip() + "\n"
        cand_src = "\n".join(clines[start:]).rstrip() + "\n"

    if "--out" in sys.argv:
        d = sys.argv[sys.argv.index("--out") + 1]
        os.makedirs(d, exist_ok=True)
        with open(os.path.join(d, "target.s"), "w", newline="\n") as fh:
            fh.write(asm + "\n")
        with open(os.path.join(d, "context.c"), "w", newline="\n") as fh:
            fh.write(cand_ctx if cand_ctx is not None else context + "\n")
        if cand_src is not None:
            with open(os.path.join(d, "source.c"), "w", newline="\n") as fh:
                fh.write(cand_src)
        print("written to", d)


if __name__ == "__main__":
    main()
