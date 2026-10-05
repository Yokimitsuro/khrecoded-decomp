#!/usr/bin/env python3
"""List small not-yet-decompiled functions with decoded instructions."""

import argparse
import json

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

from project import BUILD_DIR


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--max-size", type=int, default=16)
    parser.add_argument("--module")
    args = parser.parse_args()

    audit = json.loads((BUILD_DIR / "progress_audit.json").read_text())
    index = json.loads((BUILD_DIR / "func_index.json").read_text())
    pending = [
        item for item in audit["functions"]
        if item["category"] == "todo"
        and 0 < item["size"] <= args.max_size
        and (args.module is None or item["unit"] == args.module)
    ]
    pending.sort(key=lambda item: (item["size"], item["unit"], item["name"]))

    for item in pending:
        entry = index[item["name"]]
        mode = CS_MODE_THUMB if item["mode"] == "thumb" else CS_MODE_ARM
        decoder = Cs(CS_ARCH_ARM, mode)
        instructions = "; ".join(
            f"{insn.mnemonic} {insn.op_str}".rstrip()
            for insn in decoder.disasm(bytes.fromhex(entry["hex"]), 0)
        )
        print(
            f"{item['size']:3} {item['mode']:5} {item['unit']:6} "
            f"{item['name']} | {instructions} | rel={entry['relocs']}"
        )


if __name__ == "__main__":
    main()
