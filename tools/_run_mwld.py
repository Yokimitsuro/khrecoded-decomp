#!/usr/bin/env python3
"""Link the full ARM9 program with mwldarm.

Usage: _run_mwld.py <out.elf> <lcf> <rspfile>
"""
import os
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, LICENSE, MWLDARM, ROOT  # noqa: E402


def main():
    out_elf, lcf, rsp = sys.argv[1], sys.argv[2], sys.argv[3]

    # dsd's canonical object list picks the right file per address: compiled
    # sources for matched code, delink objects for the gaps.
    canonical = BUILD_DIR / "objects.txt"
    if canonical.exists():
        raw = [ln.strip().strip('"') for ln in canonical.read_text(encoding="utf-8").splitlines()
               if ln.strip()]
    else:
        raw = Path(rsp).read_text().split()

    # mwldarm's @rsp splitter breaks on spaces even inside quotes; paths
    # relative to ROOT (the working directory) contain none.
    objs_rel = []
    for p in raw:
        try:
            objs_rel.append(Path(p).resolve().relative_to(ROOT).as_posix())
        except ValueError:
            objs_rel.append(p.replace("\\", "/"))
    Path(rsp).write_text("\n".join(objs_rel) + "\n", encoding="utf-8", newline="\n")

    # `ALIGNALL(4)` would pad every THUMB function sitting at a 2-aligned
    # offset. Two is the THUMB minimum and preserves the original layout.
    lcf_text = Path(lcf).read_text(encoding="utf-8")
    if "ALIGNALL(4);" in lcf_text:
        Path(lcf).write_text(lcf_text.replace("ALIGNALL(4);", "ALIGNALL(2);"),
                             encoding="utf-8", newline="\n")

    # Also lower each object's .text sh_addralign for the same reason.
    subprocess.run([sys.executable, str(ROOT / "tools" / "patch_align.py"), str(rsp)], check=True)

    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    cmd = [
        str(MWLDARM),
        "-proc", "arm946e",
        # mwld decides BL vs BLX by final address; overlays overlap in address
        # space, so tools/fix_interwork.py repairs those sites after the link.
        "-interworking",
        "-map", "closure,unused",
        "-msgstyle", "gcc",
        "-nodead",
        "-nostdlib",
        "-m", "Entry",
        "-o", out_elf,
        lcf,
        f"@{rsp}",
    ]
    rc = subprocess.run(cmd, env=env, cwd=str(ROOT)).returncode
    if rc == 0:
        rc = subprocess.run([sys.executable, str(ROOT / "tools" / "fix_interwork.py"), "--write"],
                            cwd=str(ROOT)).returncode
    return rc


if __name__ == "__main__":
    sys.exit(main())
