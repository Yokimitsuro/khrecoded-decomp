#!/usr/bin/env python3
"""Rename one decomp symbol and every tracked textual reference to it.

The operation is deliberately narrow: C identifiers only, source/config trees
only, and an optional move from generated auto code to reviewed calls code.
Re-run configure after a rename so delinks are regenerated from the new path.
"""

import argparse
import re

from project import ROOT


TEXT_SUFFIXES = {".c", ".h", ".txt", ".json", ".yaml", ".yml"}
IDENTIFIER = re.compile(r"^[A-Za-z_]\w*$")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("old")
    parser.add_argument("new")
    parser.add_argument(
        "--move-calls",
        action="store_true",
        help="move the defining source from an auto directory to its sibling calls directory",
    )
    args = parser.parse_args()

    if not IDENTIFIER.fullmatch(args.old) or not IDENTIFIER.fullmatch(args.new):
        parser.error("both names must be C identifiers")
    if args.old == args.new:
        parser.error("old and new names are identical")

    pattern = re.compile(rf"\b{re.escape(args.old)}\b")
    changed = []
    definitions = []

    for root_name in ("src", "config"):
        root = ROOT / root_name
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix.lower() not in TEXT_SUFFIXES:
                continue
            text = path.read_text(encoding="utf-8")
            if re.search(rf"\b{re.escape(args.new)}\b", text):
                if path.name != f"{args.old}.c":
                    raise SystemExit(f"new symbol already appears in {path}")
            replaced, count = pattern.subn(args.new, text)
            if count:
                path.write_text(replaced, encoding="utf-8", newline="\n")
                changed.append((path, count))
            if path.name == f"{args.old}.c":
                definitions.append(path)

    if len(definitions) != 1:
        raise SystemExit(f"expected one defining source for {args.old}, found {len(definitions)}")

    source = definitions[0]
    if args.move_calls and source.parent.name == "auto":
        destination = source.parent.parent / "calls" / f"{args.new}.c"
    else:
        destination = source.with_name(f"{args.new}.c")
    if destination.exists():
        raise SystemExit(f"destination already exists: {destination}")
    destination.parent.mkdir(parents=True, exist_ok=True)
    source.rename(destination)

    print(f"{args.old} -> {args.new}")
    print(f"definition: {destination.relative_to(ROOT)}")
    print(f"updated {len(changed)} files, {sum(count for _, count in changed)} references")


if __name__ == "__main__":
    main()
