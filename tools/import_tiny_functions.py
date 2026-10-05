#!/usr/bin/env python3
"""Recover and verify trivial leaf functions directly from instruction patterns."""

import argparse
import json
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

from project import BUILD_DIR, ROOT
from verify_idx import check


HEADER = '#include "nitro/types.h"\n\n'


def destination(module: str, name: str) -> Path:
    if module.startswith("ov"):
        return ROOT / "src" / "overlays" / module / "auto" / f"{name}.c"
    return ROOT / "src" / "auto" / f"{name}.c"


def source_for(name: str, mode: str, code: bytes) -> str | None:
    decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    insns = [(item.mnemonic, item.op_str) for item in decoder.disasm(code, 0)]

    # Pointer adjustment: adds r0, #imm / add r0, r0, #imm; bx lr.
    if len(insns) == 2 and insns[1] == ("bx", "lr"):
        mnemonic, operands = insns[0]
        if mnemonic == "adds" and operands.startswith("r0, #"):
            immediate = int(operands.split("#", 1)[1], 0)
            return HEADER + (
                f"void *{name}(void *object)\n{{\n"
                f"    return (u8 *)object + 0x{immediate:x};\n"
                "}\n"
            )
        if mnemonic == "add" and operands.startswith("r0, r0, #"):
            immediate = int(operands.rsplit("#", 1)[1], 0)
            return HEADER + (
                f"void *{name}(void *object)\n{{\n"
                f"    return (u8 *)object + 0x{immediate:x};\n"
                "}\n"
            )
        if mnemonic == "add" and operands.startswith("r0, r1, #"):
            immediate = int(operands.rsplit("#", 1)[1], 0)
            return HEADER + (
                f"void *{name}(void *unused, void *object)\n{{\n"
                "    (void)unused;\n"
                f"    return (u8 *)object + 0x{immediate:x};\n"
                "}\n"
            )
        if mnemonic == "ldr" and operands.startswith("r0, [r0"):
            offset = 0 if operands == "r0, [r0]" else int(operands.split("#", 1)[1].rstrip("]"), 0)
            return HEADER + (
                f"u32 {name}(const void *object)\n{{\n"
                f"    return *(const u32 *)((const u8 *)object + 0x{offset:x});\n"
                "}\n"
            )
        if mnemonic == "str" and operands.startswith("r1, [r0"):
            offset = 0 if operands == "r1, [r0]" else int(operands.split("#", 1)[1].rstrip("]"), 0)
            return HEADER + (
                f"void {name}(void *object, u32 value)\n{{\n"
                f"    *(u32 *)((u8 *)object + 0x{offset:x}) = value;\n"
                "}\n"
            )

    # Byte getter through a short in-place pointer adjustment.
    if (
        len(insns) == 3
        and insns[0][0] == "adds"
        and insns[0][1].startswith("r0, #")
        and insns[1] == ("ldrb", "r0, [r0]")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u8 {name}(const void *object)\n{{\n"
            f"    return *((const u8 *)object + 0x{offset:x});\n"
            "}\n"
        )

    # Word getter through a short in-place pointer adjustment.
    if (
        len(insns) == 3
        and insns[0][0] == "adds"
        and insns[0][1].startswith("r0, #")
        and insns[1] == ("ldr", "r0, [r0]")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    return *(const u32 *)((const u8 *)object + 0x{offset:x});\n"
            "}\n"
        )

    # Word loaded through a pointer field.
    if (
        len(insns) == 3
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1][0] == "ldr"
        and insns[1][1].startswith("r0, [r0, #")
        and insns[2] == ("bx", "lr")
    ):
        outer = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        inner = int(insns[1][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    const u8 *nested = *(const u8 *const *)((const u8 *)object + 0x{outer:x});\n"
            f"    return *(const u32 *)(nested + 0x{inner:x});\n"
            "}\n"
        )

    # Add a caller-provided byte offset to a pointer field.
    if (
        len(insns) == 3
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1] == ("adds", "r0, r0, r1")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"void *{name}(const void *object, u32 index)\n{{\n"
            f"    u8 *base = *(u8 *const *)((const u8 *)object + 0x{offset:x});\n"
            "    return base + index;\n"
            "}\n"
        )

    # Large constant pointer adjustment materialized as MOV/LSL/ADD.
    if (
        len(insns) == 4
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r1, #")
        and insns[1][0] == "lsls"
        and insns[1][1].startswith("r1, r1, #")
        and insns[2] == ("adds", "r0, r0, r1")
        and insns[3] == ("bx", "lr")
    ):
        value = int(insns[0][1].split("#", 1)[1], 0)
        shift = int(insns[1][1].rsplit("#", 1)[1], 0)
        offset = value << shift
        return HEADER + (
            f"void *{name}(void *object)\n{{\n"
            f"    return (u8 *)object + 0x{offset:x};\n"
            "}\n"
        )

    # Store a third argument at a field of the second argument.
    if (
        len(insns) == 2
        and insns[0][0] == "str"
        and insns[0][1].startswith("r2, [r1, #")
        and insns[1] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"void {name}(void *unused, void *object, u32 value)\n{{\n"
            "    (void)unused;\n"
            f"    *(u32 *)((u8 *)object + 0x{offset:x}) = value;\n"
            "}\n"
        )

    # Difference of the leading signed words in two records.
    if insns == [
        ("ldr", "r2, [r0]"),
        ("ldr", "r0, [r1]"),
        ("subs", "r0, r2, r0"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"s32 {name}(const s32 *left, const s32 *right)\n{{\n"
            "    return *left - *right;\n"
            "}\n"
        )

    # Word setter through a short in-place pointer adjustment.
    if (
        len(insns) == 3
        and insns[0][0] == "adds"
        and insns[0][1].startswith("r0, #")
        and insns[1] == ("str", "r1, [r0]")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void {name}(void *object, u32 value)\n{{\n"
            f"    *(u32 *)((u8 *)object + 0x{offset:x}) = value;\n"
            "}\n"
        )

    return None


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--max-size", type=int, default=12)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    audit = json.loads((BUILD_DIR / "progress_audit.json").read_text())
    index = json.loads((BUILD_DIR / "func_index.json").read_text())
    trial_dir = BUILD_DIR / "tiny_candidates"
    trial_dir.mkdir(parents=True, exist_ok=True)
    matches = []

    for item in audit["functions"]:
        if item["category"] != "todo" or not (0 < item["size"] <= args.max_size):
            continue
        entry = index[item["name"]]
        if entry["relocs"]:
            continue
        source = source_for(item["name"], item["mode"], bytes.fromhex(entry["hex"]))
        if source is None:
            continue
        trial = trial_dir / f"{item['name']}.c"
        trial.write_text(source, encoding="utf-8", newline="\n")
        rc, verdict = check(str(trial), item["name"], item["mode"] == "thumb")
        if rc != 0:
            continue
        matches.append((item, source, verdict))

    matches.sort(key=lambda value: (value[0]["unit"], value[0]["name"]))
    print(
        f"verified {len(matches)} trivial functions, "
        f"{sum(item['size'] for item, _, _ in matches)} bytes"
    )
    for item, _, verdict in matches:
        print(f"{item['unit']} {item['name']} ({item['size']} bytes): {verdict}")

    if args.apply:
        for item, source, _ in matches:
            path = destination(item["unit"], item["name"])
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(source, encoding="utf-8", newline="\n")
        print(f"imported {len(matches)} functions")


if __name__ == "__main__":
    main()
