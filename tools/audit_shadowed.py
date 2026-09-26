#!/usr/bin/env python3
"""Find functions that have real C in auto/ or calls/ AND an asm_stubs/ twin.

Such a function is miscounted as an ASM stub and may be built from the stub
while finished C sits next to it unused.

    python tools/audit_shadowed.py            # report only
    python tools/audit_shadowed.py --verify   # also verify each real C
    python tools/audit_shadowed.py --fix      # verify, then delete stubs whose C matches

--fix never deletes a stub whose C does not verify: then the C is the broken
file (move it to nonmatching/) and the stub keeps the build byte-exact.
Re-run the full gate (tools/gate.sh) after --fix.
"""
import os
import subprocess
import sys

TREES = ("src", "libs")


def scan():
    real, stub = {}, {}
    for tree in TREES:
        if not os.path.isdir(tree):
            continue
        for root, _dirs, files in os.walk(tree):
            for f in files:
                if not f.endswith(".c"):
                    continue
                path = os.path.join(root, f).replace(os.sep, "/")
                if "asm_stubs" in root:
                    stub[f[:-2]] = path
                elif "nonmatching" not in root:
                    real[f[:-2]] = path
    return real, stub


def verify(path, name):
    """Try ARM, then THUMB (a THUMB function verified as ARM looks like broken C)."""
    line = "?"
    for extra in ([], ["--thumb"]):
        r = subprocess.run([sys.executable, "tools/verify_idx.py", path, name] + extra,
                           capture_output=True, text=True)
        out = (r.stdout + r.stderr).strip().splitlines()
        line = out[0] if out else "?"
        if ">>> MATCH <<<" in line:
            return line + ("  (thumb)" if extra else "")
    return line


def main():
    do_verify = "--verify" in sys.argv or "--fix" in sys.argv
    real, stub = scan()
    both = sorted(set(real) & set(stub))
    print("shadowed functions (real C + asm_stubs twin): %d" % len(both))
    if not both:
        return
    if not do_verify:
        for n in both:
            print("   " + stub[n])
        print("\nre-run with --verify to compile-check, or --fix to delete the safe ones")
        return

    ok, bad = [], []
    for n in both:
        line = verify(real[n], n)
        (ok if ">>> MATCH <<<" in line else bad).append((n, line))
    print("  real C verifies (stub safe to delete): %d" % len(ok))
    print("  real C does NOT verify (stub is load-bearing): %d" % len(bad))
    for n, line in bad:
        print("     BAD %-26s %s" % (n, line[:60]))

    if "--fix" in sys.argv:
        for n, _ in ok:
            os.remove(stub[n])
        print("\ndeleted %d stubs; re-run the full gate." % len(ok))


if __name__ == "__main__":
    main()
