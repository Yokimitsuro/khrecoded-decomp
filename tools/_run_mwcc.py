#!/usr/bin/env python3
"""Compile one source with mwccarm for the ninja build.

Usage: _run_mwcc.py <out.o> <in.c> [--mode=arm|thumb] [--cc=default|<mwccarm dir>]

The environment variable (LM_LICENSE_FILE) is set here because ninja cannot
reliably do it through `cmd /c` when paths contain spaces.
"""
import json
import os
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, CFLAGS, LICENSE, MWCC_DIR, MWCCARM, ROOT  # noqa: E402


def load_json_retry(path, attempts=20):
    """Read a generated JSON sidecar across a concurrent write window."""
    for attempt in range(attempts):
        try:
            text = path.read_text(encoding="utf-8")
            if not text.strip():
                raise json.JSONDecodeError("empty sidecar", text, 0)
            return json.loads(text)
        except (OSError, json.JSONDecodeError):
            if attempt + 1 == attempts:
                raise
            time.sleep(0.05 * (attempt + 1))


def main():
    out_path = Path(sys.argv[1])
    src_path = Path(sys.argv[2])
    rel = src_path.resolve().relative_to(ROOT).as_posix()

    opt_mode = opt_cc = None
    for a in sys.argv[3:]:
        if a.startswith("--mode="):
            opt_mode = a[len("--mode="):]
        elif a.startswith("--cc="):
            opt_cc = a[len("--cc="):]

    # Without explicit options (a direct call) fall back to the sidecar maps
    # that gen_delinks.py / configure.py produce.
    extra = []
    if opt_mode is None:
        modes_path = BUILD_DIR / "file_modes.json"
        if modes_path.exists():
            opt_mode = load_json_retry(modes_path).get(rel, "arm")
    if opt_mode == "thumb":
        extra.append("-thumb")

    mwcc_bin = MWCCARM
    if opt_cc is None:
        comp_path = BUILD_DIR / "file_compilers.json"
        if comp_path.exists():
            opt_cc = load_json_retry(comp_path).get(rel)
    if opt_cc and opt_cc != "default":
        mwcc_bin = MWCC_DIR / opt_cc / "mwccarm.exe"

    flags = list(CFLAGS)
    if opt_cc == "2.0/sp2p3":
        flags.extend(["-fp", "soft", "-ipa", "file"])
    if src_path.suffix.lower() in (".cpp", ".cp", ".cc"):
        flags[flags.index("c99")] = "c++"

    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    cmd = [str(mwcc_bin), "-c", *flags, *extra, "-o", str(out_path), str(src_path)]

    # The FLEXlm license check fails intermittently under a parallel build: an
    # arbitrary translation unit dies and the same command succeeds on its own.
    # A real diagnostic fails every attempt and is reported as usual.
    for attempt in range(8):
        r = subprocess.run(cmd, env=env, capture_output=True, text=True)
        if r.returncode == 0:
            sys.stdout.write(r.stdout)
            sys.stderr.write(r.stderr)
            # mwcc emits one section per global and orders them by its own rule;
            # put data sections back in address order so a source that owns a
            # data range lays it down where its delinks claim says.
            from reorder_data_sections import reorder
            reorder(out_path)
            from share_bss import share, wants_sharing
            if wants_sharing(src_path):
                share(out_path)
            return 0
        time.sleep(0.25 * (attempt + 1))

    sys.stdout.write(r.stdout)
    sys.stderr.write(r.stderr)
    return r.returncode


if __name__ == "__main__":
    sys.exit(main())
