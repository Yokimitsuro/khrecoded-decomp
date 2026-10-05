#!/usr/bin/env python3
"""Recover and verify trivial leaf functions directly from instruction patterns."""

import argparse
import json
import re
from functools import lru_cache
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

from project import BUILD_DIR, ROOT
from verify_idx import check


HEADER = '#include "nitro/types.h"\n\n'


@lru_cache(maxsize=None)
def current_symbol_name(original_name: str) -> str:
    """Resolve an address-style name to a semantic name already in symbols.txt."""
    match = re.search(r"_([0-9a-fA-F]{8})$", original_name)
    if match is None:
        return original_name
    address = int(match.group(1), 16)
    candidates = []
    symbol_pattern = re.compile(
        r"^(\S+)\s+kind:function(?:\([^)]*\))?\s+addr:0x([0-9a-fA-F]+)",
        re.MULTILINE,
    )
    overlay_match = re.match(r"func_(ov[0-9]+)_", original_name)
    if overlay_match:
        paths = [ROOT / "config" / "arm9" / "overlays" / overlay_match.group(1) / "symbols.txt"]
    else:
        paths = [ROOT / "config" / "arm9" / "symbols.txt"]
    for path in paths:
        if not path.exists():
            continue
        for name, address_text in symbol_pattern.findall(path.read_text(encoding="utf-8")):
            if int(address_text, 16) == address:
                candidates.append(name)
    semantic = [name for name in candidates if not name.startswith("func_")]
    return semantic[0] if semantic else (candidates[0] if candidates else original_name)


def destination(module: str, name: str) -> Path:
    if module.startswith("ov"):
        return ROOT / "src" / "overlays" / module / "auto" / f"{name}.c"
    return ROOT / "src" / "auto" / f"{name}.c"


def source_for(name: str, mode: str, code: bytes, relocs: list[list]) -> str | None:
    decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB if mode == "thumb" else CS_MODE_ARM)
    # A relocation may belong either to an instruction (BL/BLX) or to a
    # trailing literal-pool word. Cutting at the first relocation therefore
    # discarded almost every call wrapper. Decode through the first terminal
    # return/tail-call instead; any bytes after it are the local literal pool.
    insns = []
    for item in decoder.disasm(code, 0):
        insns.append((item.mnemonic, item.op_str))
        if item.mnemonic == "bx" or (item.mnemonic == "pop" and "pc" in item.op_str):
            break

    # Accessors for a global which stores an object pointer. The exact external
    # symbol is retained, so relocation verification remains as strict as the
    # instruction-byte comparison.
    if len(relocs) == 1 and relocs[0][1].startswith("data_"):
        symbol = relocs[0][1]
        pointer_header = HEADER + f"extern u8 *{symbol};\n\n"

        if (
            len(insns) == 4
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1] == ("ldr", "r0, [r0]")
            and insns[2][0] in {"ldr", "ldrh", "ldrb"}
            and insns[2][1].startswith("r0, [r0")
            and insns[3] == ("bx", "lr")
        ):
            offset = 0 if insns[2][1] == "r0, [r0]" else int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
            value_type = {"ldr": "u32", "ldrh": "u16", "ldrb": "u8"}[insns[2][0]]
            return pointer_header + (
                f"{value_type} {name}(void)\n{{\n"
                f"    return *(const {value_type} *)({symbol} + 0x{offset:x});\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1] == ("ldr", "r1, [r1]")
            and insns[2][0] in {"str", "strh", "strb"}
            and insns[2][1].startswith("r0, [r1")
            and insns[3] == ("bx", "lr")
        ):
            offset = 0 if insns[2][1] == "r0, [r1]" else int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
            value_type = {"str": "u32", "strh": "u16", "strb": "u8"}[insns[2][0]]
            return pointer_header + (
                f"void {name}({value_type} value)\n{{\n"
                f"    *({value_type} *)({symbol} + 0x{offset:x}) = value;\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1] == ("ldr", "r0, [r0]")
            and insns[2][0] == "adds"
            and insns[2][1].startswith("r0, #")
            and insns[3] == ("bx", "lr")
        ):
            offset = int(insns[2][1].split("#", 1)[1], 0)
            return pointer_header + (
                f"void *{name}(void)\n{{\n"
                f"    return {symbol} + 0x{offset:x};\n"
                "}\n"
            )

        if (
            len(insns) == 6
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1] == ("ldr", "r0, [r0]")
            and insns[2][0] in {"ldr", "ldrh", "ldrb"}
            and insns[2][1].startswith("r1, [r0")
            and insns[3][0] == "movs"
            and insns[3][1].startswith("r0, #")
            and insns[4] == ("ands", "r0, r1")
            and insns[5] == ("bx", "lr")
        ):
            offset = 0 if insns[2][1] == "r1, [r0]" else int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
            mask = int(insns[3][1].split("#", 1)[1], 0)
            value_type = {"ldr": "u32", "ldrh": "u16", "ldrb": "u8"}[insns[2][0]]
            return pointer_header + (
                f"u32 {name}(void)\n{{\n"
                f"    return *(const {value_type} *)({symbol} + 0x{offset:x}) & 0x{mask:x};\n"
                "}\n"
            )

        if (
            len(insns) == 5
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1][0] == "movs"
            and insns[1][1].startswith("r1, #")
            and insns[2] == ("ldr", "r0, [r0]")
            and insns[3][0] in {"str", "strh", "strb"}
            and insns[3][1].startswith("r1, [r0")
            and insns[4] == ("bx", "lr")
        ):
            value = int(insns[1][1].split("#", 1)[1], 0)
            offset = 0 if insns[3][1] == "r1, [r0]" else int(insns[3][1].split("#", 1)[1].rstrip("]"), 0)
            value_type = {"str": "u32", "strh": "u16", "strb": "u8"}[insns[3][0]]
            return pointer_header + (
                f"void {name}(void)\n{{\n"
                f"    *({value_type} *)({symbol} + 0x{offset:x}) = {value};\n"
                "}\n"
            )

        # Direct byte-addressed table rather than a global pointer variable.
        if (
            len(insns) == 3
            and insns[0][0] == "ldr"
            and insns[0][1].startswith("r1, [pc")
            and insns[1] == ("adds", "r0, r0, r1")
            and insns[2] == ("bx", "lr")
        ):
            return HEADER + f"extern u8 {symbol}[];\n\n" + (
                f"void *{name}(u32 offset)\n{{\n"
                f"    return {symbol} + offset;\n"
                "}\n"
            )

    # Small wrappers around one external routine. Only the forms whose complete
    # calling convention is visible in the instructions are proposed; the normal
    # relocation-aware verifier rejects wrong ARM/Thumb veneers or prototypes.
    if len(relocs) == 1 and not relocs[0][1].startswith("data_"):
        target = current_symbol_name(relocs[0][1])
        call_header = HEADER + f"extern u32 {target}();\n\n"

        if (
            len(insns) == 4
            and insns[0][0] == "push"
            and insns[1][0] in {"bl", "blx"}
            and insns[2][0] in {"mov", "movs"}
            and insns[2][1].startswith("r0, #")
            and insns[3][0] == "pop"
        ):
            result = int(insns[2][1].split("#", 1)[1], 0)
            return call_header + (
                f"u32 {name}(void *argument)\n{{\n"
                f"    {target}(argument);\n"
                f"    return {result};\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0][0] == "push"
            and insns[1][0] in {"bl", "blx"}
            and insns[2][0] == "ldr"
            and insns[2][1].startswith("r0, [r0")
            and insns[3][0] == "pop"
        ):
            offset = 0 if insns[2][1] == "r0, [r0]" else int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
            return call_header + (
                f"u32 {name}(void *argument)\n{{\n"
                f"    const u8 *result = (const u8 *){target}(argument);\n"
                f"    return *(const u32 *)(result + 0x{offset:x});\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0][0] == "push"
            and insns[1][0] in {"bl", "blx"}
            and insns[2][0] == "adds"
            and insns[2][1].startswith("r0, #")
            and insns[3][0] == "pop"
        ):
            offset = int(insns[2][1].split("#", 1)[1], 0)
            return call_header + (
                f"void *{name}(void *argument)\n{{\n"
                f"    return (u8 *){target}(argument) + 0x{offset:x};\n"
                "}\n"
            )

        if (
            len(insns) == 3
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1][0] in {"mov", "movs"}
            and insns[1][1].startswith("r1, #")
            and insns[2][0] == "bx"
        ):
            argument = int(insns[1][1].split("#", 1)[1], 0)
            return call_header + (
                f"u32 {name}(void *object)\n{{\n"
                f"    return {target}(object, {argument});\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1][0] in {"mov", "movs"}
            and insns[1][1].startswith("r0, #")
            and insns[2][0] in {"mov", "movs"}
            and insns[2][1].startswith("r1, #")
            and insns[3][0] == "bx"
        ):
            first = int(insns[1][1].split("#", 1)[1], 0)
            second = int(insns[2][1].split("#", 1)[1], 0)
            return call_header + (
                f"u32 {name}(void)\n{{\n"
                f"    return {target}({first}, {second});\n"
                "}\n"
            )

        if (
            len(insns) == 3
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1][0] in {"add", "adds"}
            and insns[1][1].startswith("r0, r0, #")
            and insns[2][0] == "bx"
        ):
            offset = int(insns[1][1].rsplit("#", 1)[1], 0)
            return call_header + (
                f"u32 {name}(void *object)\n{{\n"
                f"    return {target}((u8 *)object + 0x{offset:x});\n"
                "}\n"
            )

        if (
            len(insns) == 3
            and insns[0][0] == "ldr"
            and "[pc" in insns[0][1]
            and insns[1][0] == "asrs"
            and insns[1][1].startswith("r0, r0, #")
            and insns[2][0] == "bx"
        ):
            shift = int(insns[1][1].rsplit("#", 1)[1], 0)
            return call_header + (
                f"u32 {name}(s32 value)\n{{\n"
                f"    return {target}(value >> {shift});\n"
                "}\n"
            )

        if (
            len(insns) == 4
            and insns[0] == ("lsls", "r0, r0, #0x10")
            and insns[1][0] == "ldr"
            and "[pc" in insns[1][1]
            and insns[2] == ("lsrs", "r0, r0, #0x10")
            and insns[3][0] == "bx"
        ):
            return call_header + (
                f"u32 {name}(u32 value)\n{{\n"
                f"    return {target}((u16)value);\n"
                "}\n"
            )

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

    # Thumb form of a fixed bit test on a word field.
    if (
        len(insns) == 4
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r1, [r0, #")
        and insns[1][0] == "movs"
        and insns[1][1].startswith("r0, #")
        and insns[2] == ("ands", "r0, r1")
        and insns[3] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        mask = int(insns[1][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    return *(const u32 *)((const u8 *)object + 0x{offset:x}) & 0x{mask:x};\n"
            "}\n"
        )

    # Store the third argument in a large-offset field of the second argument.
    if (
        len(insns) == 4
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r0, #")
        and insns[1][0] == "lsls"
        and insns[1][1].startswith("r0, r0, #")
        and insns[2] == ("str", "r2, [r1, r0]")
        and insns[3] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1], 0) << int(insns[1][1].rsplit("#", 1)[1], 0)
        return HEADER + (
            f"void {name}(void *unused, void *object, u32 value)\n{{\n"
            "    (void)unused;\n"
            f"    *(u32 *)((u8 *)object + 0x{offset:x}) = value;\n"
            "}\n"
        )

    # Write a constant through the third argument and return a dispatch code.
    if (
        len(insns) == 4
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r0, #")
        and insns[1] == ("str", "r0, [r2]")
        and insns[2][0] == "movs"
        and insns[2][1].startswith("r0, #")
        and insns[3] == ("bx", "lr")
    ):
        value = int(insns[0][1].split("#", 1)[1], 0)
        result = int(insns[2][1].split("#", 1)[1], 0)
        return HEADER + (
            f"u32 {name}(void *unused0, void *unused1, u32 *output)\n{{\n"
            "    (void)unused0;\n"
            "    (void)unused1;\n"
            f"    *output = {value};\n"
            f"    return {result};\n"
            "}\n"
        )

    # Initialize one byte field and clear two related flags.
    if insns == [
        ("strb", "r1, [r0, #0x14]"),
        ("movs", "r1, #0"),
        ("strb", "r1, [r0, #0x17]"),
        ("strb", "r1, [r0, #6]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(void *object, u8 value)\n{{\n"
            "    u8 *bytes = object;\n"
            "    bytes[0x14] = value;\n"
            "    bytes[0x17] = 0;\n"
            "    bytes[6] = 0;\n"
            "}\n"
        )

    # Clear a word and initialize the adjacent halfword pair.
    if insns == [
        ("movs", "r2, #0"),
        ("str", "r2, [r0]"),
        ("strh", "r2, [r0, #4]"),
        ("strh", "r1, [r0, #6]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(void *record, u16 value)\n{{\n"
            "    *(u32 *)record = 0;\n"
            "    *(u16 *)((u8 *)record + 4) = 0;\n"
            "    *(u16 *)((u8 *)record + 6) = value;\n"
            "}\n"
        )

    # Read a halfword through an indexed pointer table.
    if insns == [
        ("lsls", "r1, r1, #2"),
        ("adds", "r0, r0, r1"),
        ("ldr", "r0, [r0, #0x70]"),
        ("ldrh", "r0, [r0, #4]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"u16 {name}(const void *table, u32 index)\n{{\n"
            "    const u8 *entry = *(const u8 *const *)((const u8 *)table + index * 4 + 0x70);\n"
            "    return *(const u16 *)(entry + 4);\n"
            "}\n"
        )

    # Read a pointer from a large-offset table and advance to its payload.
    if (
        len(insns) == 5
        and insns[0][0] == "movs"
        and insns[0][1].startswith("r1, #")
        and insns[1][0] == "lsls"
        and insns[1][1].startswith("r1, r1, #")
        and insns[2] == ("ldr", "r0, [r0, r1]")
        and insns[3][0] == "adds"
        and insns[3][1].startswith("r0, #")
        and insns[4] == ("bx", "lr")
    ):
        field = int(insns[0][1].split("#", 1)[1], 0) << int(insns[1][1].rsplit("#", 1)[1], 0)
        payload = int(insns[3][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void *{name}(const void *object)\n{{\n"
            f"    u8 *nested = *(u8 *const *)((const u8 *)object + 0x{field:x});\n"
            f"    return nested + 0x{payload:x};\n"
            "}\n"
        )

    # Pointer field followed by a constant payload offset.
    if (
        len(insns) == 3
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1][0] == "add"
        and insns[1][1].startswith("r0, r0, #")
        and insns[2] == ("bx", "lr")
    ):
        field = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        payload = int(insns[1][1].rsplit("#", 1)[1], 0)
        return HEADER + (
            f"void *{name}(const void *object)\n{{\n"
            f"    return *(u8 *const *)((const u8 *)object + 0x{field:x}) + 0x{payload:x};\n"
            "}\n"
        )

    # Sum two halfword fields with a halfword result.
    if insns == [
        ("ldrh", "r1, [r0]"),
        ("ldrh", "r0, [r0, #4]"),
        ("adds", "r0, r1, r0"),
        ("lsls", "r0, r0, #0x10"),
        ("lsrs", "r0, r0, #0x10"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"u16 {name}(const void *object)\n{{\n"
            "    const u8 *bytes = object;\n"
            "    return *(const u16 *)bytes + *(const u16 *)(bytes + 4);\n"
            "}\n"
        )

    # Initialize a state field from another word field and return zero.
    if (
        len(insns) == 6
        and insns[0] == ("movs", "r1, #0x10")
        and insns[1] == ("strh", "r1, [r0, #0x2c]")
        and insns[2][0] == "ldr"
        and insns[2][1].startswith("r1, [r0, #")
        and insns[3] == ("str", "r1, [r0, #0x30]")
        and insns[4] == ("movs", "r0, #0")
        and insns[5] == ("bx", "lr")
    ):
        source_offset = int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"u32 {name}(void *object)\n{{\n"
            "    u8 *bytes = object;\n"
            "    *(u16 *)(bytes + 0x2c) = 0x10;\n"
            f"    *(u32 *)(bytes + 0x30) = *(const u32 *)(bytes + 0x{source_offset:x});\n"
            "    return 0;\n"
            "}\n"
        )

    # Clear all four words of a 16-byte record in the original store order.
    if insns == [
        ("movs", "r1, #0"),
        ("str", "r1, [r0]"),
        ("str", "r1, [r0, #0xc]"),
        ("str", "r1, [r0, #8]"),
        ("str", "r1, [r0, #4]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(u32 fields[4])\n{{\n"
            "    fields[0] = 0;\n"
            "    fields[3] = 0;\n"
            "    fields[2] = 0;\n"
            "    fields[1] = 0;\n"
            "}\n"
        )

    # Load a word after a large pointer adjustment.
    if (
        len(insns) == 3
        and insns[0][0] == "add"
        and insns[0][1].startswith("r0, r0, #")
        and insns[1][0] == "ldr"
        and insns[1][1].startswith("r0, [r0, #")
        and insns[2] == ("bx", "lr")
    ):
        high = int(insns[0][1].rsplit("#", 1)[1], 0)
        low = int(insns[1][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"u32 {name}(const void *object)\n{{\n"
            f"    return *(const u32 *)((const u8 *)object + 0x{high + low:x});\n"
            "}\n"
        )

    # Clear caller-selected bits from a word field.
    if insns == [
        ("ldr", "r2, [r0, #4]"),
        ("mvn", "r1, r1"),
        ("and", "r1, r2, r1"),
        ("str", "r1, [r0, #4]"),
        ("bx", "lr"),
    ]:
        return HEADER + (
            f"void {name}(void *object, u32 mask)\n{{\n"
            "    *(u32 *)((u8 *)object + 4) &= ~mask;\n"
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

    # Boolean view of a word field.  The explicit comparison is important:
    # mwcc keeps the CMP/BX sequence used by the original Thumb leaf.
    if (
        len(insns) == 3
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r0, #")
        and insns[1] == ("cmp", "r0, #0")
        and insns[2] == ("bx", "lr")
    ):
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + (
            f"BOOL {name}(const void *object)\n{{\n"
            f"    return *(const u32 *)((const u8 *)object + 0x{offset:x}) != 0;\n"
            "}\n"
        )

    # Signed-halfword accessors around a shared record lookup.
    if (
        len(relocs) == 1
        and len(insns) == 5
        and insns[0][0] == "push"
        and insns[1][0] in {"bl", "blx"}
        and insns[2][0] == "movs"
        and insns[2][1].startswith("r1, #")
        and insns[3] == ("ldrsh", "r0, [r0, r1]")
        and insns[4][0] == "pop"
    ):
        target = current_symbol_name(relocs[0][1])
        offset = int(insns[2][1].split("#", 1)[1], 0)
        return HEADER + f"extern void *{target}();\n\n" + (
            f"s32 {name}(void *owner, s32 index)\n{{\n"
            f"    const u8 *record = {target}(owner, index);\n"
            f"    return *(const s16 *)(record + 0x{offset:x});\n"
            "}\n"
        )

    # The compiler sometimes loads a full word before narrowing it to s16.
    if (
        len(relocs) == 1
        and len(insns) == 6
        and insns[0][0] == "push"
        and insns[1][0] in {"bl", "blx"}
        and insns[2][0] == "ldr"
        and insns[2][1].startswith("r0, [r0, #")
        and insns[3] == ("lsls", "r0, r0, #0x10")
        and insns[4] == ("asrs", "r0, r0, #0x10")
        and insns[5][0] == "pop"
    ):
        target = current_symbol_name(relocs[0][1])
        offset = int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
        return HEADER + f"extern void *{target}();\n\n" + (
            f"s32 {name}(void *owner, s32 index)\n{{\n"
            f"    const u8 *record = {target}(owner, index);\n"
            f"    return (s16)*(const u32 *)(record + 0x{offset:x});\n"
            "}\n"
        )

    # Tail wrapper which supplies two small constants after the caller's r0.
    if (
        len(relocs) == 1
        and len(insns) == 4
        and insns[0][0] == "ldr"
        and "[pc" in insns[0][1]
        and insns[1][0] == "movs"
        and insns[1][1].startswith("r1, #")
        and insns[2][0] == "movs"
        and insns[2][1].startswith("r2, #")
        and insns[3][0] == "bx"
    ):
        target = current_symbol_name(relocs[0][1])
        first = int(insns[1][1].split("#", 1)[1], 0)
        second = int(insns[2][1].split("#", 1)[1], 0)
        return HEADER + f"extern u32 {target}();\n\n" + (
            f"u32 {name}(void *object)\n{{\n"
            f"    return {target}(object, {first}, {second});\n"
            "}\n"
        )

    # Call one routine with a constant and return a fixed dispatch result.
    if (
        len(relocs) == 1
        and len(insns) == 5
        and insns[0][0] == "push"
        and insns[1][0] == "movs"
        and insns[1][1].startswith("r0, #")
        and insns[2][0] in {"bl", "blx"}
        and insns[3][0] == "movs"
        and insns[3][1].startswith("r0, #")
        and insns[4][0] == "pop"
    ):
        target = current_symbol_name(relocs[0][1])
        argument = int(insns[1][1].split("#", 1)[1], 0)
        result = int(insns[3][1].split("#", 1)[1], 0)
        return HEADER + f"extern void {target}();\n\n" + (
            f"u32 {name}(void)\n{{\n"
            f"    {target}({argument});\n"
            f"    return {result};\n"
            "}\n"
        )

    # Tail wrappers which obtain their primary argument through an owner field.
    if (
        len(relocs) == 1
        and len(insns) in {3, 4}
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r0, [r1, #")
        and insns[1][0] == "ldr"
        and "[pc" in insns[1][1]
        and insns[-1][0] == "bx"
    ):
        target = current_symbol_name(relocs[0][1])
        offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        if len(insns) == 4 and insns[2] == ("adds", "r1, r2, #0"):
            return HEADER + f"extern u32 {target}();\n\n" + (
                f"u32 {name}(void *unused, const void *owner, u32 argument)\n{{\n"
                "    (void)unused;\n"
                f"    void *object = *(void *const *)((const u8 *)owner + 0x{offset:x});\n"
                f"    return {target}(object, argument);\n"
                "}\n"
            )
        if len(insns) == 3:
            return HEADER + f"extern u32 {target}();\n\n" + (
                f"u32 {name}(void *unused, const void *owner)\n{{\n"
                "    (void)unused;\n"
                f"    void *object = *(void *const *)((const u8 *)owner + 0x{offset:x});\n"
                f"    return {target}(object, owner);\n"
                "}\n"
            )

    # Address an element when the base and stride fields require separate loads.
    if (
        len(insns) == 6
        and insns[0][0] == "ldr"
        and insns[0][1].startswith("r2, [r0, #")
        and insns[1][0] == "adds"
        and insns[1][1].startswith("r0, #")
        and insns[2] == ("ldrh", "r0, [r0]")
        and insns[3] == ("muls", "r1, r0, r1")
        and insns[4] == ("adds", "r0, r2, r1")
        and insns[5] == ("bx", "lr")
    ):
        base_offset = int(insns[0][1].split("#", 1)[1].rstrip("]"), 0)
        stride_offset = int(insns[1][1].split("#", 1)[1], 0)
        return HEADER + (
            f"void *{name}(const void *object, u32 index)\n{{\n"
            f"    const u8 *base = *(u8 *const *)((const u8 *)object + 0x{base_offset:x});\n"
            f"    u16 stride = *(const u16 *)((const u8 *)object + 0x{stride_offset:x});\n"
            "    return (void *)(base + stride * index);\n"
            "}\n"
        )

    # Bit accessor through a pointer stored in a large-offset owner field.
    if (
        len(insns) == 6
        and insns[0][0] == "adds"
        and insns[0][1].startswith("r0, #")
        and insns[1] == ("ldr", "r0, [r0]")
        and insns[2][0] == "ldr"
        and insns[2][1].startswith("r0, [r0, #")
        and insns[3][0] == "lsls"
        and insns[4][0] == "lsrs"
        and insns[5] == ("bx", "lr")
    ):
        owner_offset = int(insns[0][1].split("#", 1)[1], 0)
        value_offset = int(insns[2][1].split("#", 1)[1].rstrip("]"), 0)
        left = int(insns[3][1].rsplit("#", 1)[1], 0)
        right = int(insns[4][1].rsplit("#", 1)[1], 0)
        bit = right - left
        return HEADER + (
            f"u32 {name}(const void *owner)\n{{\n"
            f"    const u8 *record = *(u8 *const *)((const u8 *)owner + 0x{owner_offset:x});\n"
            f"    return (*(const u32 *)(record + 0x{value_offset:x}) >> {bit}) & 1;\n"
            "}\n"
        )

    # Large ARM pointer adjustment emitted as two encodable immediates.
    if (
        len(insns) == 3
        and insns[0][0] == "add"
        and insns[0][1].startswith("r0, r0, #")
        and insns[1][0] == "add"
        and insns[1][1].startswith("r0, r0, #")
        and insns[2] == ("bx", "lr")
    ):
        first = int(insns[0][1].rsplit("#", 1)[1], 0)
        second = int(insns[1][1].rsplit("#", 1)[1], 0)
        return HEADER + (
            f"void *{name}(void *object)\n{{\n"
            f"    return (u8 *)object + 0x{first + second:x};\n"
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
        source = source_for(
            item["name"], item["mode"], bytes.fromhex(entry["hex"]), entry["relocs"]
        )
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
