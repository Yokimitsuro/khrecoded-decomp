#!/usr/bin/env python3
"""Classify every function for the progress reports.

Categories:
  c_decompiled_matched  real C source in an auto/ or calls/ directory
  asm_stub_matched      ASM-based source (asm_stubs/, inline asm, .s)
  named                 no source yet, but a real (non-placeholder) name
  todo                  no source, placeholder func_XXXXXXXX name

Only the first counts as C decompilation progress; see docs/PROGRESS_POLICY.md.
Byte-exactness itself is proved by tools/verify_idx.py and the module gate,
not by this script.

    python tools/audit_progress.py     # writes build/progress_audit.{json,md}
"""
import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, ROOT  # noqa: E402
import data_progress  # noqa: E402

SUBTREES = ["auto", "calls", "asm_stubs/auto", "asm_stubs/calls"]
PLACEHOLDER = re.compile(r"^func_(?:ov\d{3}_)?[0-9a-f]{8}$")
CATEGORIES = ("c_decompiled_matched", "asm_stub_matched", "named", "todo")


def _discover_src_dirs():
    """src/{auto,calls,asm_stubs/*}, src/overlays/ovNNN/..., libs/<lib>/<module>/..."""
    out = [ROOT / "src" / sub for sub in SUBTREES]
    ov_root = ROOT / "src" / "overlays"
    if ov_root.exists():
        for ov in sorted(ov_root.iterdir()):
            if ov.is_dir():
                out.extend(ov / sub for sub in SUBTREES)
    libs_root = ROOT / "libs"
    if libs_root.exists():
        for top in sorted(libs_root.iterdir()):
            if not top.is_dir():
                continue
            for mod in sorted(top.iterdir()):
                if mod.is_dir():
                    out.extend(mod / sub for sub in SUBTREES)
    return out


SRC_DIRS = _discover_src_dirs()

ASM_RE = re.compile("|".join([
    r"^\s*asm\s*(?:\{|\()",
    r"^\s*asm\s+[A-Za-z_]\w*\s*\**\s*[A-Za-z_]\w*\s*\(",
    r"\basm\s+(?:void|int|unsigned|signed|char|short|long|float|double|\*)",
    r"\b__asm\b", r"\bINLINE_ASM\b", r"\bNON_MATCHING\b", r"\bGLOBAL_ASM\b", r"\bINCLUDE_ASM\b",
]), re.M)

SYM_RE = re.compile(r"(\S+)\s+kind:function\((arm|thumb),[^\r\n]*size=0x([0-9a-fA-F]+)[^\r\n]*\)\s+addr:0x([0-9a-fA-F]+)")


def source_category(path):
    if path.suffix == ".s" or "asm_stubs" in path.parts:
        return "asm_stub_matched"
    if ASM_RE.search(path.read_text(encoding="utf-8", errors="replace")):
        return "asm_stub_matched"
    return "c_decompiled_matched"


def load_functions():
    """name -> {unit, mode, size, addr} from every symbols.txt."""
    out = {}
    for path in (ROOT / "config").glob("**/symbols.txt"):
        text = str(path).replace("\\", "/")
        m = re.search(r"overlays/(ov\d+)", text)
        unit = m.group(1) if m else "itcm" if "/itcm/" in text else "dtcm" if "/dtcm/" in text else "main"
        with path.open(encoding="utf-8", errors="replace") as f:
            for line in f:
                s = SYM_RE.match(line)
                if s:
                    out[s.group(1)] = {"unit": unit, "mode": s.group(2),
                                       "size": int(s.group(3), 16), "addr": int(s.group(4), 16)}
    return out


def load_sources():
    by_name = {}
    for src_dir in SRC_DIRS:
        if not src_dir.exists():
            continue
        for path in sorted(list(src_dir.glob("*.c")) + list(src_dir.glob("*.cpp")) + list(src_dir.glob("*.s"))):
            by_name[path.stem] = {"path": path.relative_to(ROOT).as_posix(), "category": source_category(path)}
    return by_name


def classify_functions():
    funcs = load_functions()
    sources = load_sources()
    out = []
    for name, info in sorted(funcs.items()):
        src = sources.get(name)
        if src:
            category, path = src["category"], src["path"]
        else:
            category, path = ("todo" if PLACEHOLDER.match(name) else "named"), None
        out.append({"name": name, "unit": info["unit"], "size": info["size"], "mode": info["mode"],
                    "category": category, "source": path})
    unknown = [s for n, s in sources.items() if n not in funcs]
    return out, unknown


def summarize(functions, unknown, data_units=None):
    counts, sizes = Counter(), Counter()
    units = defaultdict(Counter)
    for f in functions:
        counts[f["category"]] += 1
        sizes[f["category"]] += f["size"]
        units[f["unit"]][f["category"]] += 1
    data = data_progress.summarize(data_units or data_progress.load_data_units())
    return {
        "total_functions": len(functions),
        "total_code_bytes": sum(f["size"] for f in functions),
        "counts": {c: counts.get(c, 0) for c in CATEGORIES},
        "code_bytes": {c: sizes.get(c, 0) for c in CATEGORIES},
        "unknown_source_files": len(unknown),
        "units": {u: dict(c) for u, c in sorted(units.items())},
        "data": data,
    }


def write_markdown(summary):
    labels = {
        "c_decompiled_matched": "Real C matched",
        "asm_stub_matched": "ASM stub matched",
        "named": "Named, not decompiled",
        "todo": "Not decompiled",
    }
    total_f, total_b = summary["total_functions"], summary["total_code_bytes"]
    rows = []
    for c, label in labels.items():
        n, b = summary["counts"][c], summary["code_bytes"][c]
        rows.append("| %s | %d | %.1f%% | %d | %.1f%% |" % (
            label, n, 100.0 * n / total_f if total_f else 0, b, 100.0 * b / total_b if total_b else 0))
    return "\n".join([
        "# Progress audit", "",
        "Generated by `python tools/audit_progress.py`.", "",
        "| Category | Functions | Function % | Code bytes | Code % |",
        "|---|---:|---:|---:|---:|",
        *rows, "",
        "Source files that match no function in symbols.txt: %d" % summary["unknown_source_files"], "",
        "## DATA", "",
        "| Category | Bytes or symbols | % |",
        "|---|---:|---:|",
        "| Reconstructed byte-exact DATA | %s / %s | %.2f%% |" % (
            format(summary["data"]["matched_data_bytes"], ","),
            format(summary["data"]["total_data_bytes"], ","),
            100.0 * summary["data"]["matched_data_bytes"] / summary["data"]["total_data_bytes"]
            if summary["data"]["total_data_bytes"] else 100.0),
        "| Named DATA symbols | %s / %s | %.2f%% |" % (
            format(summary["data"]["named_data_symbols"], ","),
            format(summary["data"]["total_data_symbols"], ","),
            100.0 * summary["data"]["named_data_symbols"] / summary["data"]["total_data_symbols"]
            if summary["data"]["total_data_symbols"] else 100.0), "",
    ])


def main():
    functions, unknown = classify_functions()
    summary = summarize(functions, unknown)
    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "progress_audit.json").write_text(
        json.dumps({"summary": summary, "functions": functions, "unknown_sources": unknown},
                   indent=1, sort_keys=True) + "\n", encoding="utf-8")
    (BUILD_DIR / "progress_audit.md").write_text(write_markdown(summary), encoding="utf-8", newline="\n")
    c = summary["counts"]
    d = summary["data"]
    print("progress_audit -> C=%d, ASM=%d, named=%d, todo=%d, total=%d; DATA=%d/%d bytes" % (
        c["c_decompiled_matched"], c["asm_stub_matched"], c["named"], c["todo"], summary["total_functions"],
        d["matched_data_bytes"], d["total_data_bytes"]))


if __name__ == "__main__":
    main()
