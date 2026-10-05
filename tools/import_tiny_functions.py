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

    # Clear the first two words of a small record.
    if insns == [
        ("movs", "r1, #0"),
        ("str", "r1, [r0]"),
        ("str", "r1, [r0, #4]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(u32 fields[2])\n{{\n"
            "    fields[0] = 0;\n"
            "    fields[1] = 0;\n"
            "}\n"
        )

    # Initialize a two-word command record with a constant tag and payload.
    if (
        len(insns) == 4
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r2, #")
        and insns[1] == ("str", "r2, [r0]")
        and insns[2] == ("str", "r1, [r0, #4]")
        and insns[3] == ("bx", "lr")
    ):
        tag = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void {name}(u32 fields[2], u32 payload)\n{{\n"
            f"    fields[0] = {tag};\n"
            "    fields[1] = payload;\n"
            "}\n"
        )

    # Read a byte from an object reached through a pointer field.
    if (
        len(insns) == 4
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1][0] == "adds"
        and insns[1][1].startswith("r0, #")
        and insns[2] == ("ldrb", "r0, [r0]")
        and insns[3] == ("bx", "lr")
    ):
        outer = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        inner = int(insns[1][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u8 {name}(const void *object)\n{{\n"
            f"    const u8 *nested = *(const u8 *const *)((const u8 *)object + 0x{outer:x});\n"
            f"    return nested[0x{inner:x}];\n"
            "}\n"
        )

    # Read a byte from a four-byte-stride table reached through a pointer field.
    if (
        len(insns) == 4
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r2, [r0, #")
        and insns[1] == ("lsls", "r0, r1, #2")
        and insns[2] == ("ldrb", "r0, [r2, r0]")
        and insns[3] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"u8 {name}(const void *object, u32 index)\n{{\n"
            f"    const u8 *table = *(const u8 *const *)((const u8 *)object + 0x{offset:x});\n"
            "    return table[index * 4];\n"
            "}\n"
        )

    # Large-offset word field accessor materialized as MOV/LSL.
    if (
        len(insns) == 4
        and insns[0][0] == "movs"
        and insns[1][0] == "lsls"
        and insns[3] == ("bx", "lr")
    ):
        register, immediate_text = insns[0][1].split(", #")
        shift_parts = insns[1][1].split(", #")
        if shift_parts[0] == f"{register}, {register}":
            offset = int(immediate_text, 0) << int(shift_parts[1], 0)
            if insns[2] == ("str", f"r1, [r0, {register}]"):
                return HEADER + (
                    f"void {name}(void *object, u32 value)\n{{\n"
                    f"    *(u32 *)((u8 *)object + 0x{offset:x}) = value;\n"
                    "}\n"
                )
            if insns[2] == ("ldr", f"r0, [r0, {register}]"):
                return HEADER + (
                    f"u32 {name}(const void *object)\n{{\n"
                    f"    return *(const u32 *)((const u8 *)object + 0x{offset:x});\n"
                    "}\n"
                )

    # Copy a word from the second argument and return a small dispatch code.
    if (
        len(insns) == 4
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r1, [r1")
        and insns[1][0] == "str"
        and insns[1][1].startswith("r1, [r0, #")
        and insns[2][0] == "movs"
        and insns[2][1].startswith("r0, #")
        and insns[3] == ("bx", "lr")
    ):
        source_offset = 0 if insns[0][1] == "r1, [r1]" else int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        destination_offset = int(insns[1][1].split("#", 1)[1].rstrip("]"), 0)
        result = int(insns[2][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u32 {name}(void *destination, const void *source)\n{{\n"
            f"    *(u32 *)((u8 *)destination + 0x{destination_offset:x}) = "
            f"*(const u32 *)((const u8 *)source + 0x{source_offset:x});\n"
            f"    return {result};\n"
            "}\n"
        )

    # Test a word or halfword field against a constant mask.
    if (
        len(insns) == 3
        and insns[0][0] in {"ldr", "ldrh"}
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1][0] == "and"
        and insns[1][1].startswith("r0, r0, #")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        mask = int(insns[1][1].rsplit("#", 1)[1], 0)
        field_type = "u16" if insns[0][0] == "ldrh" else "u32"
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    return *(const {field_type} *)((const u8 *)object + 0x{offset:x}) & 0x{mask:x};\n"
            "}\n"
        )

    # OR a mask into a word field.
    if (
        len(insns) == 4
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r2, [r0, #")
        and insns[1] == ("orr", "r1, r2, r1")
        and insns[2][0] == "str"
        and insns[2][1].startswith("r1, [r0, #")
        and insns[3] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        if int(insns[2][1].split("#", 1)[1].rstrip("]"), 0) == offset:
            return HEADER + (
                f"void {name}(void *object, u32 mask)\n{{\n"
                f"    *(u32 *)((u8 *)object + 0x{offset:x}) |= mask;\n"
                "}\n"
            )

    # Initialize a command record containing a tag and two halfword arguments.
    if (
        len(insns) == 5
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r3, #")
        and insns[1] == ("str", "r3, [r0]")
        and insns[2] == ("strh", "r1, [r0, #4]")
        and insns[3] == ("strh", "r2, [r0, #6]")
        and insns[4] == ("bx", "lr")
    ):
        tag = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void {name}(void *record, u16 first, u16 second)\n{{\n"
            f"    *(u32 *)record = {tag};\n"
            "    *(u16 *)((u8 *)record + 4) = first;\n"
            "    *(u16 *)((u8 *)record + 6) = second;\n"
            "}\n"
        )

    # Address an element using a halfword stride stored beside a base pointer.
    if (
        len(insns) == 5
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r2, [r0, #")
        and insns[1][0] == "ldrh"
        and insns[1][1].startswith("r0, [r0, #")
        and insns[2] == ("muls", "r1, r0, r1")
        and insns[3] == ("adds", "r0, r2, r1")
        and insns[4] == ("bx", "lr")
    ):
        base_offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        stride_offset = int(insns[1][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"void *{name}(const void *object, u32 index)\n{{\n"
            f"    u8 *base = *(u8 *const *)((const u8 *)object + 0x{base_offset:x});\n"
            f"    u16 stride = *(const u16 *)((const u8 *)object + 0x{stride_offset:x});\n"
            "    return base + stride * index;\n"
            "}\n"
        )

    # Address an element using a signed halfword stride.
    if (
        len(insns) == 5
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r3, #")
        and insns[1][0] == "ldrsh"
        and insns[1][1] == "r0, [r0, r3]"
        and insns[2] == ("muls", "r0, r1, r0")
        and insns[3] == ("adds", "r0, r2, r0")
        and insns[4] == ("bx", "lr")
    ):
        stride_offset = int(insns[0][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void *{name}(const void *object, s32 index, void *base)\n{{\n"
            f"    s16 stride = *(const s16 *)((const u8 *)object + 0x{stride_offset:x});\n"
            "    return (u8 *)base + index * stride;\n"
            "}\n"
        )

    # Test a field after a short pointer adjustment (Thumb immediate encoding).
    if (
        len(insns) == 5
        and insns[0][0] == "adds"
        and insns[0][1].startswith("r0, #")
        and insns[1][0] in {"ldr", "ldrh"}
        and insns[1][1] == "r1, [r0]"
        and insns[2][0] == "movs"
        and insns[2][1].startswith("r0, #")
        and insns[3] == ("ands", "r0, r1")
        and insns[4] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1], 0)
        mask = int(insns[2][1].split("#", 1)[1], 0)
        field_type = "u16" if insns[1][0] == "ldrh" else "u32"
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    return *(const {field_type} *)((const u8 *)object + 0x{offset:x}) & 0x{mask:x};\n"
            "}\n"
        )

    # Clear the mixed-size header of a small record.
    if insns == [
        ("movs", "r1, #0"),
        ("str", "r1, [r0]"),
        ("str", "r1, [r0, #4]"),
        ("strb", "r1, [r0, #8]"),
        ("str", "r1, [r0, #0xc]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(void *record)\n{{\n"
            "    *(u32 *)record = 0;\n"
            "    *(u32 *)((u8 *)record + 4) = 0;\n"
            "    *((u8 *)record + 8) = 0;\n"
            "    *(u32 *)((u8 *)record + 0xc) = 0;\n"
            "}\n"
        )

    # Sum the three word fields used for a packed buffer offset.
    if insns == [
        ("ldr", "r2, [r0, #8]"),
        ("ldr", "r1, [r0, #0x18]"),
        ("ldr", "r0, [r0, #0x1c]"),
        ("adds", "r0, r1, r0"),
        ("adds", "r0, r2, r0"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            "    const u8 *bytes = object;\n"
            "    return *(const u32 *)(bytes + 8) + *(const u32 *)(bytes + 0x18) + "
            "*(const u32 *)(bytes + 0x1c);\n"
            "}\n"
        )

    # Load one field, shift it, store it back, and report success.
    if (
        len(insns) == 5
        and insns[0] == ("ldr", "r0, [r1]")
        and insns[1][0] == "lsls"
        and insns[1][1].startswith("r0, r0, #")
        and insns[2] == ("str", "r0, [r1]")
        and insns[3] == ("movs", "r0, #1")
        and insns[4] == ("bx", "lr")
    ):
        shift = int(insns[1][1].rsplit("#", 1)[1], 0)
        return HEADER + (
            f"u32 {name}(void *unused, u32 *value)\n{{\n"
            "    (void)unused;\n"
            f"    *value <<= {shift};\n"
            "    return 1;\n"
            "}\n"
        )

    # Increment one field and report success.
    if insns == [
        ("ldr", "r0, [r2]"),
        ("adds", "r0, r0, #1"),
        ("str", "r0, [r2]"),
        ("movs", "r0, #1"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"u32 {name}(void *unused0, void *unused1, u32 *value)\n{{\n"
            "    (void)unused0;\n"
            "    (void)unused1;\n"
            "    ++*value;\n"
            "    return 1;\n"
            "}\n"
        )

    # Absolute value implemented branchlessly in ARM mode.
    if insns == [
        ("eor", "r1, r0, r0, asr #31"),
        ("sub", "r0, r1, r0, asr #31"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"s32 {name}(s32 value)\n{{\n"
            "    return value < 0 ? -value : value;\n"
            "}\n"
        )

    # Mask a word field with a caller-provided value.
    if insns == [
        ("ldr", "r0, [r0, #4]"),
        ("and", "r0, r0, r1"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"u32 {name}(const void *object, u32 mask)\n{{\n"
            "    return *(const u32 *)((const u8 *)object + 4) & mask;\n"
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
