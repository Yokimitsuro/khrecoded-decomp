#!/usr/bin/env python3
"""Regenerate the status table of README.md between its progress markers.

    python tools/update_readme.py

Everything outside `<!-- progress:start -->` / `<!-- progress:end -->` is left
untouched. Uses the same classification as tools/progress.py.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import audit_progress  # noqa: E402
from project import GAME_CODE, ROOT  # noqa: E402

START, END = "<!-- progress:start -->", "<!-- progress:end -->"


def table():
    functions, _unknown = audit_progress.classify_functions()
    total = len(functions)
    total_bytes = sum(f["size"] for f in functions)

    def count(cat):
        return sum(1 for f in functions if f["category"] == cat)

    def size(cat):
        return sum(f["size"] for f in functions if f["category"] == cat)

    c, asm, named = count("c_decompiled_matched"), count("asm_stub_matched"), count("named")
    c_b, asm_b = size("c_decompiled_matched"), size("asm_stub_matched")
    pct = lambda a, b: 100.0 * a / b if b else 0.0  # noqa: E731
    rows = [
        ("Real C matched functions", "**{:,}** / {:,} ({:.1f}%)".format(c, total, pct(c, total)),
         "Functions implemented in C and verified byte-exact"),
        ("Real C matched **bytes**", "**{:,}** / {:,} ({:.2f}%)".format(c_b, total_bytes, pct(c_b, total_bytes)),
         "Code bytes covered by real C; the honest progress figure"),
        ("Assembly matched functions", "**{:,}** ({:,} bytes)".format(asm, asm_b),
         "Original SDK, BIOS and DS Protect assembly, verified byte-exact; never counted as C"),
        ("Named, not decompiled", "**{:,}**".format(named),
         "Functions with a known name (SDK, NitroSystem, ...) but no source yet"),
        ("Total known functions", "**{:,}**".format(total), "Functions in the dsd symbol tables"),
        ("Region", "EU (`%s`)" % GAME_CODE, ""),
        ("Compiler", "CodeWarrior `mwccarm` 3.0 build 139", "Same toolchain and flags as khdays-decomp"),
    ]
    lines = ["| Category | Count | Meaning |", "|---|---:|---|"]
    lines += ["| %s | %s | %s |" % r for r in rows]
    return "\n".join(lines)


def main():
    path = ROOT / "README.md"
    text = path.read_text(encoding="utf-8")
    if START not in text or END not in text:
        raise SystemExit("README.md has no progress markers")
    head, rest = text.split(START, 1)
    _old, tail = rest.split(END, 1)
    path.write_text(head + START + "\n" + table() + "\n" + END + tail, encoding="utf-8", newline="\n")
    print("README.md status table updated")


if __name__ == "__main__":
    main()
