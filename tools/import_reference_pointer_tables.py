#!/usr/bin/env python3
"""Import reference ARM9 function-pointer tables after remapping US targets to EU."""

import argparse
import collections
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "build" / "reference_ricky"
MANIFEST = REFERENCE / "data_matches.json"
RESULTS = ROOT / "build" / "reference_batch_results.json"
CONFIG = ROOT / "config" / "arm9"
SYMBOLS = CONFIG / "symbols.txt"
DELINKS = CONFIG / "delinks.txt"
REFERENCE_DELINKS = REFERENCE / "config" / "bk9e" / "arm9" / "delinks.txt"
COMPILERS = CONFIG / "file_compilers.json"
BINARY = ROOT / "dsd_extract" / "arm9" / "arm9.bin"

EXTERN_RE = re.compile(r"extern void (\w+)_([0-9a-fA-F]{8})\(void\);")
PLAIN_EXTERN_RE = re.compile(r"extern void (\w+)\(void\);")
DATA_EXTERN_RE = re.compile(r"extern u8 (\w+)_([0-9a-fA-F]{8})\[\];")
ANY_EXTERN_RE = re.compile(r"^extern ", re.MULTILINE)
TABLE_RE = re.compile(
    r"void\s+\(\*\s*(const\s+)?(\w+)\[(\d+)\]\)\(void\)\s*=\s*"
    r"\{(.*?)\};",
    re.S,
)
SECTION_RE = re.compile(
    r"^\s+\.(text|rodata|data|ctor|bss)\s+"
    r"start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)"
)
FUNCTION_RE = re.compile(
    r"^(\S+)\s+kind:function\((arm|thumb),size=0x([0-9a-fA-F]+)\)\s+"
    r"addr:0x([0-9a-fA-F]+)$",
    re.MULTILINE,
)
DATA_RE = re.compile(
    r"^(\S+)(\s+kind:data\([^)]*\)\s+addr:0x([0-9a-fA-F]+).*)$",
    re.MULTILINE,
)
PLACEHOLDER_RE = re.compile(r"^data_[0-9a-fA-F]{8}$")

TABLE_NAMES = {
    0x02052EEC: "sAllocatorFuncForExpHeap",
    0x02052EFC: "sVramTransferTaskHandlers",
    0x02052964: "CARDiDmaUsingFormer",
    0x020555C4: "gBgAffineControlDispatch",
    0x02055644: "gBgExtendedControlDispatch",
    0x0205576C: "gBg0TransferDispatch",
    0x02055774: "gBgLayerTransferDispatch",
    0x020558A0: "gCollisionTestSphereDispatch",
    0x020558B4: "gCollisionTestPairDispatch",
    0x02055930: "gCollisionSweepSphereDispatch",
    0x02055944: "gCollisionSweepPairDispatch",
    0x020559C0: "gCollisionBoundsDispatch",
    0x02055BD8: "OSi_ProtectionRegionSetters",
    0x02055C4C: "sDefaultAllocTexVramFunc",
    0x02055C50: "sDefaultFreeTexVramFunc",
    0x02055C54: "sDefaultAllocPlttVramFunc",
    0x02055C58: "sDefaultFreePlttVramFunc",
    0x02055C5C: "sFrmTexVramRegionOrder",
    0x02055C64: "sFrmTexVramNormalRegions",
    0x02055CF4: "NNS_G3dFuncAnmVisNsBvaDefault",
    0x02055CFC: "NNS_G3dFuncAnmMatNsBtaDefault",
    0x02055D00: "NNS_G3dFuncAnmMatNsBtpDefault",
    0x02055D04: "NNS_G3dFuncAnmMatNsBmaDefault",
    0x02055D64: "gJointAnimationResultDispatch",
    0x02055D70: "gJointAnimationNodeDispatch",
    0x02055D7C: "gMaterialAnimationDispatch",
    0x02055F30: "gGameTitleStringTable",
    0x02055FF8: "gLanguageCodeTable",
    0x0205615C: "gSoundCategoryNames",
}

TARGET_NAMES = {
    **{0x02003C00 + index * 8: f"OS_SetProtectionRegion{index}" for index in range(8)},
    **{0x02003C40 + index * 8: f"OS_GetProtectionRegion{index}" for index in range(8)},
    0x0201375C: "Gfd_DefaultAllocTexVram",
    0x02013764: "Gfd_DefaultFreeTexVram",
    0x0201376C: "Gfd_DefaultAllocPlttVram",
    0x02013774: "Gfd_DefaultFreePlttVram",
    0x02013674: "AllocatorAllocForExpHeap",
    0x02013688: "AllocatorFreeForExpHeap",
    0x020136E0: "AllocatorAllocForSDKHeap",
    0x020136FC: "AllocatorFreeForSDKHeap",
}


def module_layout(path: Path) -> tuple[dict[str, tuple[int, int]], list[tuple[str, int, int]]]:
    sections = {}
    claims = []
    in_header = True
    for line in path.read_text(encoding="utf-8").splitlines():
        if in_header and not line.strip():
            in_header = False
            continue
        match = SECTION_RE.match(line)
        if not match:
            continue
        section = match.group(1)
        start, end = int(match.group(2), 16), int(match.group(3), 16)
        if in_header:
            sections[section] = (start, end)
        elif section != "text":
            claims.append((section, start, end))
    return sections, claims


def find_all(data: bytes, needle: bytes, base: int) -> list[int]:
    matches = []
    offset = 0
    while True:
        offset = data.find(needle, offset)
        if offset < 0:
            return matches
        matches.append(base + offset)
        offset += 1


def replace_data_symbol(text: str, old: str, new: str, address: int) -> str:
    pattern = re.compile(
        rf"^{re.escape(old)}(\s+kind:data\([^)]*\)\s+"
        rf"addr:0x{address:08x}.*)$",
        re.MULTILINE,
    )
    text, count = pattern.subn(new + r"\1", text)
    if count != 1:
        raise RuntimeError(f"DATA symbol not found once: {old} at 0x{address:08x}")
    return text


def discover() -> list[dict]:
    results = json.loads(RESULTS.read_text(encoding="utf-8"))
    address_map = {
        item["us"]["address"]: item
        for item in results
        if item.get("result") == "match"
    }
    dominant_delta = collections.Counter(
        item["eu"]["address"] - item["us"]["address"]
        for item in results
        if item.get("result") == "match"
    ).most_common(1)[0][0]
    symbols_text = SYMBOLS.read_text(encoding="utf-8")
    function_symbols_text = (
        symbols_text
        + "\n"
        + (CONFIG / "itcm" / "symbols.txt").read_text(encoding="utf-8")
    )
    functions = {
        int(match.group(4), 16): {
            "name": match.group(1),
            "mode": match.group(2),
            "size": int(match.group(3), 16),
        }
        for match in FUNCTION_RE.finditer(function_symbols_text)
    }
    reference_functions = {
        int(match.group(4), 16): {
            "name": match.group(1),
            "mode": match.group(2),
            "size": int(match.group(3), 16),
        }
        for match in FUNCTION_RE.finditer(
            (REFERENCE / "config" / "bk9e" / "arm9" / "symbols.txt").read_text(
                encoding="utf-8"
            )
        )
    }
    functions_by_name = {item["name"]: item for item in functions.values()}
    data_symbols = {}
    for match in DATA_RE.finditer(symbols_text):
        data_symbols.setdefault(int(match.group(3), 16), []).append(match.group(1))

    sections, claims = module_layout(DELINKS)
    reference_sections, _ = module_layout(REFERENCE_DELINKS)
    binary = BINARY.read_bytes()
    base = sections["text"][0]
    entries = json.loads(MANIFEST.read_text(encoding="utf-8"))["data"]
    candidates = []
    section_deltas = {}
    for entry in entries:
        if entry.get("origin") != "generated table" or entry["module"] != "arm9":
            continue
        us_start, us_end = int(entry["start"], 16), int(entry["end"], 16)
        if us_start not in TABLE_NAMES:
            continue
        source = (REFERENCE / entry["source"]).read_text(encoding="utf-8")
        externs = EXTERN_RE.findall(source)
        suffixed_names = {f"{name}_{address}" for name, address in externs}
        plain_externs = [
            name for name in PLAIN_EXTERN_RE.findall(source)
            if name not in suffixed_names
        ]
        data_externs = DATA_EXTERN_RE.findall(source)
        if (
            len(externs) + len(plain_externs) + len(data_externs)
            != len(ANY_EXTERN_RE.findall(source))
        ):
            continue
        targets = {}
        valid = True
        for old_name, address_text in externs:
            old_full_name = f"{old_name}_{address_text}"
            mapping = address_map.get(int(address_text, 16))
            if mapping is not None:
                eu_address = mapping["eu"]["address"]
                current = functions.get(eu_address)
                semantic = mapping["match"]["name"]
            else:
                us_address = int(address_text, 16)
                target_name = TARGET_NAMES.get(us_address)
                current = functions_by_name.get(target_name or old_full_name)
                reference_function = reference_functions.get(us_address)
                translated = functions.get(us_address + dominant_delta)
                translated_matches = (
                    reference_function is not None
                    and translated is not None
                    and reference_function["mode"] == translated["mode"]
                    and reference_function["size"] == translated["size"]
                )
                if (
                    current is None
                    and reference_function is not None
                    and reference_function["name"].startswith("func_")
                    and translated_matches
                ):
                    current = translated
                if current is None:
                    current = functions_by_name.get(old_name)
                if current is None and us_address < 0x02000000:
                    current = functions.get(us_address)
                if current is None and translated_matches:
                    current = translated
                eu_address = None if current is None else next(
                    address for address, item in functions.items() if item is current
                )
                semantic = old_name
            if current is None or eu_address is None:
                valid = False
                break
            if mapping is None and target_name is not None:
                semantic = target_name
            if semantic == "func" or semantic.startswith("func_"):
                semantic = current["name"]
            targets[old_full_name] = {
                "symbol": current["name"],
                "semantic": semantic,
                "address": eu_address,
                "mode": current["mode"],
                "kind": "function",
            }
        for name in plain_externs:
            current = functions_by_name.get(name)
            if current is None:
                valid = False
                break
            address = next(
                address for address, item in functions.items() if item is current
            )
            targets[name] = {
                "symbol": current["name"],
                "semantic": name,
                "address": address,
                "mode": current["mode"],
                "kind": "function",
            }
        for old_name, address_text in data_externs:
            old_full_name = f"{old_name}_{address_text}"
            address = int(address_text, 16)
            names = data_symbols.get(address, [])
            if len(names) != 1:
                valid = False
                break
            targets[old_full_name] = {
                "symbol": names[0],
                "semantic": names[0],
                "address": address,
                "mode": "data",
                "kind": "data",
            }
        if not valid:
            continue

        block = bytearray(us_end - us_start)
        tables = []
        for match in TABLE_RE.finditer(source):
            is_const = bool(match.group(1))
            old_table_name = match.group(2)
            count = int(match.group(3))
            table_address = int(old_table_name.rsplit("_", 1)[-1], 16)
            raw_items = [item.strip() for item in match.group(4).split(",") if item.strip()]
            if len(raw_items) != count:
                valid = False
                break
            resolved = []
            for item in raw_items:
                item = re.sub(r"^\(void \(\*\)\(void\)\)", "", item)
                if item == "NULL":
                    resolved.append(None)
                    continue
                target = targets.get(item)
                if target is None:
                    valid = False
                    break
                pointer = target["address"] | (1 if target["mode"] == "thumb" else 0)
                resolved.append({**target, "pointer": pointer})
            if not valid:
                break
            offset = table_address - us_start
            payload = b"".join(
                struct.pack("<I", 0 if item is None else item["pointer"])
                for item in resolved
            )
            if offset < 0 or offset + len(payload) > len(block):
                valid = False
                break
            block[offset:offset + len(payload)] = payload
            if table_address == 0x02052EEC:
                split_tables = (
                    (0, 2, "sAllocatorFuncForExpHeap"),
                    (2, 2, "sAllocatorFuncForSDKHeap"),
                )
                for first, split_count, table_name in split_tables:
                    split_items = resolved[first:first + split_count]
                    tables.append({
                        "const": is_const,
                        "offset": offset + first * 4,
                        "count": split_count,
                        "items": split_items,
                        "name": table_name,
                        "kind": "function",
                    })
            else:
                table_name = TABLE_NAMES.get(table_address)
                if table_name is None:
                    valid = False
                    break
                tables.append({
                    "const": is_const,
                    "offset": offset,
                    "count": count,
                    "items": resolved,
                    "name": table_name,
                    "kind": next(
                        (item["kind"] for item in resolved if item is not None),
                        "function",
                    ),
                })
        if not valid or not tables or not block:
            continue

        section = entry["section"].lstrip(".")
        section_start, section_end = sections[section]
        raw = binary[section_start - base:section_end - base]
        occurrences = find_all(raw, bytes(block), section_start)
        if len(occurrences) == 1:
            eu_start = occurrences[0]
            section_deltas.setdefault(section, set()).add(eu_start - us_start)
        else:
            deltas = set(section_deltas.get(section, set()))
            deltas.add(sections[section][0] - reference_sections[section][0])
            if len(deltas) != 1:
                continue
            eu_start = us_start + next(iter(deltas))
            if eu_start not in occurrences:
                continue
        eu_end = eu_start + len(block)
        if any(
            section == claimed_section and eu_start < end and start < eu_end
            for claimed_section, start, end in claims
        ):
            continue
        for table in tables:
            table["address"] = eu_start + table["offset"]
            names = data_symbols.get(table["address"], [])
            if len(names) != 1:
                valid = False
                break
            if not PLACEHOLDER_RE.match(names[0]) and names[0] != table["name"]:
                valid = False
                break
            table["old_name"] = names[0]
        if not valid:
            continue
        candidates.append({
            "section": section,
            "start": eu_start,
            "end": eu_end,
            "tables": tables,
        })
    return candidates


def render_source(tables: list[dict]) -> str:
    unique_targets = {}
    for table in tables:
        for item in table["items"]:
            if item is not None:
                unique_targets[item["symbol"]] = (item["semantic"], item["kind"])
    lines = ['#include "nitro/types.h"', ""]
    for symbol, (semantic, kind) in unique_targets.items():
        comment = f" /* {semantic} */" if semantic != symbol else ""
        if kind == "function":
            lines.append(f"extern void {symbol}(void);{comment}")
        else:
            lines.append(f"extern u8 {symbol}[];")
    for table in tables:
        declaration = (
            f"void (*{'const ' if table['const'] else ''}{table['name']}"
            f"[{table['count']}])(void)"
            if table["kind"] == "function"
            else f"void *{table['name']}[{table['count']}]"
        )
        lines.extend(["", declaration + " = {"])
        for item in table["items"]:
            if item is None:
                lines.append("    NULL,")
            else:
                comment = (
                    f" /* {item['semantic']} */"
                    if item["semantic"] != item["symbol"]
                    else ""
                )
                lines.append(f"    {item['symbol']},{comment}")
        lines.append("};")
    lines.append("")
    return "\n".join(lines)


def apply(candidates: list[dict]) -> None:
    symbols = SYMBOLS.read_text(encoding="utf-8")
    delinks = DELINKS.read_text(encoding="utf-8").rstrip()
    compilers = json.loads(COMPILERS.read_text(encoding="utf-8"))
    replacements = {}
    for candidate in candidates:
        tables = candidate["tables"]
        filename = (
            f"{tables[0]['name']}.c" if len(tables) == 1
            else f"PointerTables_{candidate['start']:08x}.c"
        )
        destination = ROOT / "src" / "data" / "tables" / filename
        source = render_source(tables)
        destination.parent.mkdir(parents=True, exist_ok=True)
        if destination.exists() and destination.read_text(encoding="utf-8") != source:
            raise RuntimeError(f"destination differs: {destination}")
        destination.write_text(source, encoding="utf-8", newline="\n")
        for table in tables:
            if table["old_name"] != table["name"]:
                symbols = replace_data_symbol(
                    symbols, table["old_name"], table["name"], table["address"]
                )
                replacements[table["old_name"]] = table["name"]
        relative = destination.relative_to(ROOT).as_posix()
        compilers[relative] = "dsi/1.1"
        delinks += (
            f"\n\n{relative}:\n    complete\n"
            f"    .{candidate['section']:<10} start:0x{candidate['start']:08x} "
            f"end:0x{candidate['end']:08x}"
        )

    pattern = re.compile(
        r"\b(?:" + "|".join(re.escape(name) for name in replacements) + r")\b"
    ) if replacements else None
    for root in (ROOT / "src", ROOT / "libs"):
        for path in root.rglob("*"):
            if not path.is_file() or path.suffix not in (".c", ".h"):
                continue
            source = path.read_text(encoding="utf-8")
            updated = pattern.sub(
                lambda match: replacements[match.group(0)], source
            ) if pattern else source
            if updated != source:
                path.write_text(updated, encoding="utf-8", newline="\n")

    SYMBOLS.write_text(symbols, encoding="utf-8", newline="\n")
    DELINKS.write_text(delinks + "\n", encoding="utf-8", newline="\n")
    COMPILERS.write_text(
        json.dumps(compilers, indent=2) + "\n", encoding="utf-8", newline="\n"
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    args = parser.parse_args()
    candidates = discover()
    if args.limit:
        candidates = candidates[:args.limit]
    total = sum(item["end"] - item["start"] for item in candidates)
    for item in candidates:
        tables = item["tables"]
        print(
            f"{', '.join(table['name'] for table in tables)}: .{item['section']} "
            f"0x{item['start']:08x}-0x{item['end']:08x} "
            f"({sum(table['count'] for table in tables)} entries)"
        )
    print(f"eligible {len(candidates)} pointer tables, {total} bytes")
    if args.apply:
        apply(candidates)
        print(f"imported {len(candidates)} pointer tables, {total} bytes")


if __name__ == "__main__":
    main()
