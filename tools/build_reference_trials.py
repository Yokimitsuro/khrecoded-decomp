#!/usr/bin/env python3
"""Compile still-unported reference candidates with a selected MWCC version."""

import argparse
import concurrent.futures as futures
import json
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "build" / "reference_batch_results.json"
REFERENCE = ROOT / "build" / "reference_ricky"
SYMBOLS = ROOT / "config" / "arm9" / "symbols.txt"
RUN_MWCC = ROOT / "tools" / "_run_mwcc.py"


def compile_one(item: dict, compiler: str, output_dir: Path) -> tuple[bool, str]:
    ordinal = item["ordinal"]
    mode = item["eu"]["mode"]
    name = item["eu"]["name"]
    output = output_dir / f"{ordinal:04d}.o"
    command = [
        sys.executable,
        str(RUN_MWCC),
        str(output),
        str(REFERENCE / item["match"]["source"]),
        f"--mode={mode}",
        f"--cc={compiler}",
    ]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        message = (result.stdout + result.stderr).strip().splitlines()
        detail = message[-1] if message else "compile failed"
        return False, f"{name}: {detail}"
    return True, name


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--compiler", required=True)
    parser.add_argument("-j", "--jobs", type=int, default=16)
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()

    results = json.loads(RESULTS.read_text(encoding="utf-8"))
    symbols = SYMBOLS.read_text(encoding="utf-8")
    existing_sources = {
        path.stem
        for directory in (ROOT / "src", ROOT / "libs")
        for path in directory.rglob("*.c")
    }
    candidates = []
    for item in results:
        name = item["eu"]["name"]
        if name in existing_sources:
            continue
        if not re.search(rf"^{re.escape(name)} kind:function", symbols, re.MULTILINE):
            continue
        candidates.append(item)

    output_dir = ROOT / "build" / "reference_trials" / args.compiler.replace("/", "_")
    output_dir.mkdir(parents=True, exist_ok=True)
    if not args.force:
        candidates = [
            item for item in candidates
            if not (output_dir / f"{item['ordinal']:04d}.o").exists()
        ]

    print(f"compiling {len(candidates)} reference candidates with {args.compiler}")
    failures = []
    completed = 0
    with futures.ThreadPoolExecutor(max_workers=args.jobs) as executor:
        jobs = [executor.submit(compile_one, item, args.compiler, output_dir)
                for item in candidates]
        for job in futures.as_completed(jobs):
            ok, message = job.result()
            completed += 1
            if not ok:
                failures.append(message)
            if completed % 100 == 0:
                print(f"  {completed}/{len(candidates)}")

    print(f"compiled {completed - len(failures)}/{len(candidates)} candidates")
    for message in failures[:20]:
        print(f"  {message}")
    if failures:
        print(f"failed {len(failures)} candidates")


if __name__ == "__main__":
    main()
