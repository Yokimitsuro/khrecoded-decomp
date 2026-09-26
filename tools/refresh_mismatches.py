#!/usr/bin/env python3
"""Verify every matched source and record the ones that no longer match.

gen_delinks.py keeps the listed files out of the link, so dsd fills their
range with the original bytes and the built modules stay byte-exact while the
C is fixed.

    python tools/refresh_mismatches.py

Writes build/known_mismatches.txt and config/arm9/known_mismatches.txt (the
committed copy a fresh clone falls back to); one source path per line.
"""
import os
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import audit_progress  # noqa: E402
from project import BUILD_DIR, CONFIG_DIR, ROOT  # noqa: E402


def matched_sources():
    for src_dir in audit_progress.SRC_DIRS:
        if not src_dir.exists() or "asm_stubs" in src_dir.parts:
            continue
        for p in sorted(src_dir.glob("*.c")):
            if audit_progress.source_category(p) == "c_decompiled_matched":
                yield p.relative_to(ROOT).as_posix()


def main():
    files = list(matched_sources())
    if not files:
        raise SystemExit("no matched sources")
    lst = BUILD_DIR / "refresh_list.txt"
    BUILD_DIR.mkdir(exist_ok=True)
    lst.write_text("\n".join(files) + "\n", encoding="utf-8")
    r = subprocess.run([sys.executable, str(ROOT / "tools" / "verify_idx.py"), "--batch",
                        "-j", str(os.cpu_count() or 4), "@" + str(lst)],
                       cwd=str(ROOT), capture_output=True, text=True)
    bad = []
    seen = 0
    for line in r.stdout.splitlines():
        parts = line.split("\t")
        if len(parts) < 3:
            continue
        seen += 1
        if parts[1] != "0":
            bad.append((parts[0], parts[2]))
    if seen != len(files):
        raise SystemExit("verified %d of %d files; not writing the list\n%s" % (seen, len(files), r.stderr))
    body = "".join(path + "\n" for path, _ in sorted(bad))
    for out in (BUILD_DIR / "known_mismatches.txt", CONFIG_DIR / "known_mismatches.txt"):
        out.write_text(body, encoding="utf-8", newline="\n")
    print("verified %d matched sources, %d mismatch" % (seen, len(bad)))
    for path, why in bad[:20]:
        print("  %s  %s" % (path, why[:80]))


if __name__ == "__main__":
    main()
