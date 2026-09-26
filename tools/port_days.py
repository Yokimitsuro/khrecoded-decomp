#!/usr/bin/env python3
"""Port byte-exact C from the Kingdom Hearts 358/2 Days decompilation.

Re:coded and 358/2 Days share the NitroSDK / NNS / MSL libraries and part of
the engine. For every function of this ROM whose code equals (relocated words
masked) a function khdays-decomp already has as matching C, this tool:

  1. compiles the Days source in this function's mode (ARM or THUMB);
  2. checks the compiled bytes and relocation offsets against this ROM;
  3. maps every relocated symbol of the source to the symbol at the same
     address in this ROM, keeping the addend (so `&table + 8` still maps);
  4. writes the source with the symbols renamed.

Every written file is then verified with tools/verify_idx.py and only
byte-exact results are kept.

Options:
  --days PATH   khdays-decomp checkout (needs its build/func_index.json,
                produced there by `python tools/rebuild_index.py --write`)
  --scan        also try each Days source compiled in the OTHER mode (Days
                ARM code that this game built as THUMB, and vice versa)
  --names       apply Days names to this project's placeholder symbols where
                the evidence is one-to-one (library and engine names only)
  --asm         also port Days sources that are original library assembly
                (NitroSDK/MSL `asm` functions, BIOS veneers); they go to
                asm_stubs/ and never count as C
  --write       write sources / symbols.txt (default is a dry run)
  -j N          parallel compiler jobs

    python tools/port_days.py --days ../khdays-decomp --scan --names --write
"""
import argparse
import collections
import concurrent.futures as cf
import glob
import json
import os
import re
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, CFLAGS, FUNC_INDEX, LICENSE, MWCCARM, ROOT  # noqa: E402

WORK = BUILD_DIR / "port_days"

SYM_LINE = re.compile(r"^(\S+)\s+kind:(\w+)(?:\(([^)]*)\))?.*?\baddr:0x([0-9a-fA-F]+)")
REL_LINE = re.compile(r"^from:0x([0-9a-fA-F]+)\s+kind:(\S+)\s+to:0x([0-9a-fA-F]+)\s+module:(\S+)")
IDENT = re.compile(r"^[A-Za-z_]\w*$")
PLACEHOLDER = re.compile(r"^(?:func|data)_(?:ov\d{3}_)?[0-9a-f]{8}$")
# Names that only make sense in the Days binary: overlay-numbered prefixes,
# address-suffixed variants, compiler labels.
DAYS_SPECIFIC = re.compile(r"(?i)^ov\d+_|_ov\d{3}(_|$)|^func_|^data_|^\.|^@|\$|^_dsd|_0x[0-9a-f]{8}$|[0-9a-f]{8}")

ASM_RE = re.compile(
    r"^\s*asm\s*(?:\{|\()|^\s*asm\s+[A-Za-z_]\w*\s*\**\s*[A-Za-z_]\w*\s*\(|"
    r"\basm\s+(?:void|int|unsigned|signed|char|short|long|float|double|\*)|"
    r"\b__asm\b|\bINLINE_ASM\b|\bNON_MATCHING\b|\bGLOBAL_ASM\b|\bINCLUDE_ASM\b", re.M)

R_ARM_PC24, R_ARM_ABS32, R_ARM_THM_CALL = 1, 2, 10
CALL_TYPES = {R_ARM_PC24, R_ARM_THM_CALL, 15, 16, 28, 29}


# --------------------------------------------------------------------------
# dsd configuration of either project
# --------------------------------------------------------------------------

def module_of(path):
    p = path.replace("\\", "/")
    m = re.search(r"/overlays/(ov\d+)/", p)
    if m:
        return m.group(1)
    for name in ("itcm", "dtcm"):
        if "/%s/" % name in p:
            return name
    return "main"


class Config:
    """symbols.txt and relocs.txt of one dsd project."""

    def __init__(self, root):
        self.root = Path(root)
        self.at = collections.defaultdict(dict)       # module -> addr -> [(name, kind)]
        self.sym = {}                                  # name -> (module, addr, kind, mode, size)
        self.files = {}                                # module -> symbols.txt path
        self.relocs = collections.defaultdict(dict)   # module -> from -> (kind, to, [modules])
        for path in sorted(glob.glob(str(self.root / "config" / "arm9" / "**" / "symbols.txt"), recursive=True)):
            mod = module_of(path)
            self.files[mod] = path
            with open(path, encoding="utf-8", errors="replace") as fh:
                for line in fh:
                    m = SYM_LINE.match(line)
                    if not m:
                        continue
                    name, kind, args, addr = m.group(1), m.group(2), m.group(3) or "", int(m.group(4), 16)
                    mode = "thumb" if "thumb" in args else "arm" if "arm" in args else None
                    sm = re.search(r"size=0x([0-9a-fA-F]+)", args)
                    self.at[mod].setdefault(addr, []).append((name, kind))
                    self.sym.setdefault(name, (mod, addr, kind, mode, int(sm.group(1), 16) if sm else None))
            rpath = os.path.join(os.path.dirname(path), "relocs.txt")
            if os.path.exists(rpath):
                with open(rpath, encoding="utf-8", errors="replace") as fh:
                    for line in fh:
                        m = REL_LINE.match(line)
                        if m:
                            self.relocs[mod][int(m.group(1), 16)] = (
                                m.group(2), int(m.group(3), 16), target_modules(m.group(4)))

    def lookup(self, mods, addrs, want_code):
        """First symbol at one of `addrs` in `mods` (then main), as rebuild_index resolves it."""
        for mod in list(mods) + ["main"]:
            table = self.at.get(mod, {})
            for a in addrs:
                for name, kind in table.get(a, []):
                    if want_code and kind not in ("function", "label"):
                        continue
                    return name
        return None


def target_modules(spec):
    m = re.match(r"^overlays?\(([\d,]+)\)$", spec)
    if m:
        return ["ov%03d" % int(n) for n in m.group(1).split(",")]
    return [] if spec == "none" else [spec]


# --------------------------------------------------------------------------
# indexes and keys
# --------------------------------------------------------------------------

def masked_key(mode, data, offsets):
    b = bytearray(data)
    for off in offsets:
        b[off:off + 4] = b"\0\0\0\0"
    return (mode, bytes(b), tuple(sorted(set(offsets))))


def index_key(entry):
    return masked_key(entry["mode"], bytes.fromhex(entry["hex"]), [o for o, _ in entry["relocs"]])


def days_sources(days, asm=False):
    """Days function name -> source path (relative).

    Real C only by default; with asm=True, only the library assembly sources
    (asm_stubs/ under libs/, and hand-written .s runtime helpers).
    """
    out = {}
    for top in ("src", "libs"):
        for p in glob.glob(str(Path(days) / top / "**" / "*.*"), recursive=True):
            if not p.endswith((".c", ".s")):
                continue
            rel = Path(p).relative_to(days).as_posix()
            parts = rel.split("/")
            if "nonmatching" in parts or parts[-2] not in ("auto", "calls"):
                continue
            is_asm = p.endswith(".s") or "asm_stubs" in parts or bool(
                ASM_RE.search(Path(p).read_text(encoding="utf-8", errors="replace")))
            if asm and is_asm and top == "libs":
                out[Path(p).stem] = rel
            elif not asm and not is_asm:
                out[Path(p).stem] = rel
    return out


def lib_home(rel):
    """libs/<library>/<module> for a library source, None otherwise."""
    if rel and rel.startswith("libs/"):
        return "/".join(rel.split("/")[:3])
    return None


def existing_sources():
    names = set()
    for top in ("src", "libs"):
        for p in glob.glob(str(ROOT / top / "**" / "*.*"), recursive=True):
            if p.endswith((".c", ".cpp", ".s")):
                names.add(Path(p).stem)
    return names


# --------------------------------------------------------------------------
# compiling and reading donor objects
# --------------------------------------------------------------------------

def compile_source(src, mode, out):
    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists() and out.stat().st_mtime >= src.stat().st_mtime:
        return out
    if src.suffix == ".s":
        r = subprocess.run([sys.executable, str(ROOT / "tools" / "_run_armasm.py"), str(out), str(src)],
                           capture_output=True, text=True)
        return out if r.returncode == 0 else None
    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    cmd = [str(MWCCARM), "-c", *CFLAGS, *(["-thumb"] if mode == "thumb" else []), "-o", str(out), str(src)]
    for _ in range(4):
        r = subprocess.run(cmd, env=env, capture_output=True, text=True)
        if r.returncode == 0:
            return out
    return None


def donor_object(days, rel, mode):
    out = WORK / "obj" / mode / (rel.replace("/", "__") + ".o")
    return compile_source(Path(days) / rel, mode, out)


def read_object(path, name):
    """(text bytes, [(offset, symbol, type, addend)], problem) for function `name`."""
    with open(path, "rb") as fh:
        elf = ELFFile(fh)
        symtab = elf.get_section_by_name(".symtab")
        fsym = None
        for s in symtab.get_symbol_by_name(name) or []:
            if s["st_info"]["type"] == "STT_FUNC" and isinstance(s["st_shndx"], int):
                fsym = s
        if fsym is None:
            return None, None, "function not defined"
        idx = fsym["st_shndx"]
        # Anything else the object defines (static helpers, string literals,
        # tables) would have to be laid down by this file too. Local labels
        # inside the function itself (assembly branch targets) are harmless.
        for s in symtab.iter_symbols():
            if not isinstance(s["st_shndx"], int) or s["st_shndx"] == 0 or s.name == name:
                continue
            if s["st_info"]["type"] in ("STT_SECTION", "STT_FILE") or s.name.startswith("$") or not s.name:
                continue
            if s["st_shndx"] == idx and s["st_info"]["bind"] == "STB_LOCAL" and s["st_info"]["type"] != "STT_FUNC":
                continue
            return None, None, "object defines %s" % s.name
        text = elf.get_section(idx).data()
        relocs = []
        for sec in elf.iter_sections():
            if sec["sh_type"] not in ("SHT_REL", "SHT_RELA") or sec["sh_info"] != idx:
                continue
            for r in sec.iter_relocations():
                sym = symtab.get_symbol(r["r_info_sym"])
                if isinstance(sym["st_shndx"], int) and sym["st_shndx"] != 0 and sym.name != name:
                    return None, None, "local reference %s" % (sym.name or "section")
                addend = r["r_addend"] if sec["sh_type"] == "SHT_RELA" else 0
                relocs.append((r["r_offset"], sym.name, r["r_info_type"], addend))
        # Other code sections (a second function) disqualify the file as well.
        for i, sec in enumerate(elf.iter_sections()):
            if i != idx and sec.name == ".text" and sec["sh_size"]:
                return None, None, "several functions"
    return bytes(text), sorted(relocs), None


# --------------------------------------------------------------------------
# symbol mapping
# --------------------------------------------------------------------------

def map_symbols(cfg, rname, relocs):
    """Days symbol -> this project's symbol for one function, or (None, reason)."""
    mod, addr = cfg.sym[rname][0], cfg.sym[rname][1]
    mapping, targets = {}, {}
    for off, sym, typ, addend in relocs:
        site = cfg.relocs[mod].get(addr + off)
        if site is None:
            return None, "no relocation at 0x%08x" % (addr + off)
        kind, to, mods = site
        if not mods:
            return None, "relocation without module at 0x%08x" % (addr + off)
        if typ in CALL_TYPES:
            new = cfg.lookup(mods, [to, to & ~1], True)
        elif typ == R_ARM_ABS32:
            base = to - addend
            new = cfg.lookup(mods, [base, base & ~1] if not addend else [base], False)
        else:
            return None, "relocation type %d" % typ
        if new is None:
            return None, "no symbol for 0x%08x" % to
        if not IDENT.match(new):
            return None, "target %s is not an identifier" % new
        if mapping.setdefault(sym, new) != new:
            return None, "%s maps to both %s and %s" % (sym, mapping[sym], new)
        if targets.setdefault(new, sym) != sym:
            return None, "%s and %s both map to %s" % (targets[new], sym, new)
    return mapping, None


# --------------------------------------------------------------------------
# source rewriting
# --------------------------------------------------------------------------

COMMENT_RE = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
TOKEN_RE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*')
EXTERN_RE = re.compile(r"^\s*extern\b[^;{}()]*?\b([A-Za-z_]\w*)\s*(?:\([^;()]*\))?\s*(?:\[[^;]*\])?\s*;\s*$")


def strip_comments(text):
    def repl(m):
        s = m.group(0)
        if s.startswith("/"):
            return "" if s.startswith("//") else (" " if "\n" not in s else "\n" * s.count("\n"))
        return s
    out = COMMENT_RE.sub(repl, text)
    lines = [ln.rstrip() for ln in out.splitlines()]
    cleaned = []
    for ln in lines:
        if ln == "" and (not cleaned or cleaned[-1] == ""):
            continue
        cleaned.append(ln)
    return "\n".join(cleaned).strip("\n") + "\n"


def rename_tokens(text, mapping):
    def repl(m):
        tok = m.group(0)
        return tok if tok[0] in "\"'" else mapping.get(tok, tok)
    return TOKEN_RE.sub(repl, text)


def drop_unused_externs(text, used):
    out = []
    for line in text.splitlines():
        m = EXTERN_RE.match(line)
        if m and m.group(1) not in used:
            continue
        out.append(line)
    return "\n".join(out) + "\n"


def port_source(text, mapping, keep_comments, drop_externs):
    if not keep_comments:
        text = strip_comments(text)
    text = rename_tokens(text, mapping)
    if drop_externs:
        text = drop_unused_externs(text, set(mapping.values()))
    return text


def out_path(donor_rel, rname, rmodule, has_relocs, asm=False):
    kind = ("asm_stubs/" if asm else "") + ("calls" if has_relocs else "auto")
    ext = Path(donor_rel).suffix
    if donor_rel.startswith("libs/"):
        parts = donor_rel.split("/")
        return "/".join(parts[:3] + [kind, rname + ext])
    if rmodule.startswith("ov"):
        return "src/overlays/%s/%s/%s%s" % (rmodule, kind, rname, ext)
    return "src/%s/%s%s" % (kind, rname, ext)


# --------------------------------------------------------------------------
# names
# --------------------------------------------------------------------------

def plan_names(cfg, pairs):
    """One-to-one Days names for this project's placeholder symbols.

    Evidence comes only from functions that are identical in both ROMs as
    indexed (not from a cross-mode recompile) and at least 8 bytes long: the
    function's own name and the names of the symbols it references.
    """
    proposals = collections.defaultdict(set)
    for p in pairs:
        if not p["strong"]:
            continue
        items = [(p["rname"], p["donor"])] + [(new, old) for old, new in p["mapping"].items()]
        for rsym, dname in items:
            if PLACEHOLDER.match(rsym) and not DAYS_SPECIFIC.search(dname) and IDENT.match(dname):
                proposals[rsym].add(dname)
    by_name = collections.defaultdict(set)
    for rsym, names in proposals.items():
        for n in names:
            by_name[n].add(rsym)
    plan = {}
    for rsym, names in proposals.items():
        if len(names) != 1:
            continue
        n = next(iter(names))
        if len(by_name[n]) != 1 or n in cfg.sym:
            continue
        plan[rsym] = n
    return plan


def apply_names(cfg, plan):
    """Rename symbols in symbols.txt and in any existing source."""
    by_file = collections.defaultdict(dict)
    for old, new in plan.items():
        by_file[cfg.files[cfg.sym[old][0]]][old] = new
    for path, ren in by_file.items():
        lines = Path(path).read_text(encoding="utf-8").splitlines(keepends=True)
        for i, line in enumerate(lines):
            tok = line.split(" ", 1)[0]
            if tok in ren:
                lines[i] = ren[tok] + line[len(tok):]
        Path(path).write_text("".join(lines), encoding="utf-8", newline="\n")
    for top in ("src", "libs"):
        for p in glob.glob(str(ROOT / top / "**" / "*.c"), recursive=True):
            text = Path(p).read_text(encoding="utf-8")
            new = rename_tokens(text, plan)
            if new != text:
                Path(p).write_text(new, encoding="utf-8", newline="\n")
            stem = Path(p).stem
            if stem in plan:
                Path(p).rename(Path(p).with_name(plan[stem] + ".c"))


# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--days", required=True)
    ap.add_argument("--scan", action="store_true")
    ap.add_argument("--names", action="store_true")
    ap.add_argument("--asm", action="store_true")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("-j", type=int, default=max(1, (os.cpu_count() or 2) - 2))
    args = ap.parse_args()
    days = Path(args.days).resolve()

    R = json.loads(FUNC_INDEX.read_text())
    D = json.loads((days / "build" / "func_index.json").read_text())
    cfg = Config(ROOT)
    srcs = days_sources(days)
    asm_srcs = days_sources(days, asm=True) if args.asm else {}
    have = existing_sources()
    print("this ROM: %d functions indexed, %d with a source" % (len(R), len(have & set(R))))
    print("Days: %d real-C sources" % len(srcs))

    # How distinctive a piece of code is. A key shared by several Days
    # functions (`bx lr`, a getter) says nothing about WHICH function this is:
    # such a pair still ports the code, but carries no name and is filed by
    # this ROM's module, not under the donor's library.
    all_srcs = dict(srcs, **asm_srcs)
    dcount = collections.Counter()
    homes = collections.defaultdict(set)
    for dn, e in D.items():
        k = index_key(e)
        dcount[k] += 1
        homes[k].add(lib_home(all_srcs.get(dn)))

    def classify(e, d):
        """(strong, library) for an identical pair."""
        k = index_key(e)
        strong = e["size"] >= 8 and dcount[k] == 1
        library = (e["size"] >= 12 and lib_home(all_srcs.get(d)) is not None
                   and (dcount[k] == 1 or homes[k] == {lib_home(all_srcs.get(d))}))
        return strong, library

    # Candidate donors: identical as indexed (same mode) ...
    by_key = collections.defaultdict(list)
    for n, e in D.items():
        if n in srcs:
            by_key[index_key(e)].append(n)
    todo = {n: e for n, e in R.items() if n not in have and n in cfg.sym}
    cands = collections.defaultdict(list)   # rname -> [(donor, mode, strong, library)]
    for n, e in todo.items():
        for d in by_key.get(index_key(e), []):
            cands[n].append((d, e["mode"]) + classify(e, d))
    print("identical to a Days function with C: %d" % len(cands))
    if asm_srcs:
        asm_key = collections.defaultdict(list)
        for n, e in D.items():
            if n in asm_srcs:
                asm_key[index_key(e)].append(n)
        n_asm = 0
        for n, e in todo.items():
            if n not in cands and index_key(e) in asm_key:
                cands[n] = [(d, e["mode"], classify(e, d)[0], True) for d in asm_key[index_key(e)]]
                n_asm += 1
        srcs = dict(asm_srcs, **srcs)
        print("identical to Days library assembly: %d" % n_asm)

    # ... and, with --scan, every Days source compiled in the other mode.
    if args.scan:
        jobs = [(d, "thumb" if D[d]["mode"] == "arm" else "arm") for d in srcs
                if d in D and d not in asm_srcs]
        print("scan: compiling %d Days sources in the other mode" % len(jobs))
        with cf.ThreadPoolExecutor(args.j) as ex:
            objs = list(ex.map(lambda j: (j, donor_object(days, srcs[j[0]], j[1])), jobs))
        want = collections.defaultdict(list)
        for n, e in todo.items():
            want[index_key(e)].append(n)
        added = 0
        for (d, mode), obj in objs:
            if obj is None:
                continue
            text, relocs, why = read_object(obj, d)
            if why:
                continue
            for n in want.get(masked_key(mode, text, [r[0] for r in relocs]), []):
                if all(c[0] != d for c in cands[n]):
                    cands[n].append((d, mode, False, False))
                    added += 1
        print("scan: %d more candidate pairs" % added)

    # Compile each candidate donor in the needed mode and map its symbols.
    flat = [(n,) + c for n, lst in cands.items() for c in lst]
    with cf.ThreadPoolExecutor(args.j) as ex:
        objs = list(ex.map(lambda t: donor_object(days, srcs[t[1]], t[2]), flat))
    reasons = collections.Counter()
    pairs = {}
    for (n, d, mode, strong, library), obj in zip(flat, objs):
        if n in pairs and (pairs[n]["donor_lib"] or not library):
            continue
        if obj is None:
            reasons["donor does not compile"] += 1
            continue
        text, relocs, why = read_object(obj, d)
        if why:
            reasons[re.sub(r" \S+$", "", why)] += 1
            continue
        if masked_key(mode, text, [r[0] for r in relocs]) != index_key(R[n]):
            reasons["compiled bytes differ"] += 1
            continue
        mapping, why = map_symbols(cfg, n, relocs)
        if mapping is None:
            reasons[re.sub(r" (0x[0-9a-f]+|\S+)$", "", why)] += 1
            continue
        pairs[n] = {"rname": n, "donor": d, "mode": mode, "strong": strong,
                    "mapping": mapping, "donor_lib": library,
                    "asm": d in asm_srcs and srcs[d] == asm_srcs[d]}
    print("portable: %d functions" % len(pairs))
    for why, c in reasons.most_common():
        print("  rejected %5d  %s" % (c, why))

    plan = plan_names(cfg, pairs.values()) if args.names else {}
    if args.names:
        WORK.mkdir(parents=True, exist_ok=True)
        (WORK / "names_plan.json").write_text(json.dumps(plan, indent=1, sort_keys=True), encoding="utf-8")
        print("names: %d placeholder symbols get a Days name (build/port_days/names_plan.json)" % len(plan))
    if not args.write:
        print("dry run; pass --write to apply")
        return

    if plan:
        apply_names(cfg, plan)
        (WORK / "names.json").write_text(json.dumps(plan, indent=1, sort_keys=True), encoding="utf-8")
        # Names changed: the index is keyed by name, rebuild it from scratch.
        FUNC_INDEX.unlink()
        subprocess.run([sys.executable, str(ROOT / "tools" / "rebuild_index.py"), "--write"],
                       check=True, capture_output=True)

    written = []
    for n, p in sorted(pairs.items()):
        rname = plan.get(n, n)
        mapping = {old: plan.get(new, new) for old, new in p["mapping"].items()}
        mapping[p["donor"]] = rname
        src = (days / srcs[p["donor"]]).read_text(encoding="utf-8", errors="replace")
        donor_path = srcs[p["donor"]] if p["donor_lib"] else "src/" + Path(srcs[p["donor"]]).name
        path = ROOT / out_path(donor_path, rname, cfg.sym[n][0], bool(p["mapping"]), p["asm"])
        path.parent.mkdir(parents=True, exist_ok=True)
        variants = [port_source(src, mapping, p["donor_lib"], True),
                    port_source(src, mapping, p["donor_lib"], False)]
        written.append((path, variants))
        path.write_text(variants[0], encoding="utf-8", newline="\n")

    kept = verify([w[0] for w in written], args.j)
    retry = [(p, v) for p, v in written if p not in kept]
    for p, v in retry:
        p.write_text(v[1], encoding="utf-8", newline="\n")
    kept |= verify([p for p, _ in retry], args.j)
    dropped = 0
    for p, _ in written:
        if p not in kept:
            p.unlink()
            dropped += 1
    print("written and verified: %d (dropped %d that did not verify)" % (len(kept), dropped))


def verify(paths, jobs):
    if not paths:
        return set()
    WORK.mkdir(parents=True, exist_ok=True)
    lst = WORK / "verify_list.txt"
    lst.write_text("\n".join(str(p) for p in paths) + "\n", encoding="utf-8")
    r = subprocess.run([sys.executable, str(ROOT / "tools" / "verify_idx.py"), "--batch", "-j", str(jobs),
                        "@" + str(lst)], capture_output=True, text=True)
    ok = set()
    for line in r.stdout.splitlines():
        parts = line.split("\t")
        if len(parts) >= 3 and parts[1] == "0":
            ok.add(Path(parts[0]))
    return ok


if __name__ == "__main__":
    main()
