#!/usr/bin/env python3
"""Measure reconstructed and named data across every linked module.

The module headers in delinks.txt define the complete .rodata/.ctor/.data/.bss
ranges. Data ranges attached to complete source entries are byte-exact ranges
already accepted by the full link gate. They are merged before counting so a
range can never be counted twice.
"""
import re
from pathlib import Path

from project import module_dirs, module_name

DATA_SECTIONS = ("rodata", "ctor", "data", "bss")
SECTION_RE = re.compile(
    r"^\s+\.(rodata|data|ctor|bss)\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)"
)
SOURCE_RE = re.compile(r"^(\S+\.(?:c|cpp|s)):\s*$")
DATA_SYMBOL_RE = re.compile(r"^(\S+)\s+kind:data\([^)]*\)\s+addr:0x([0-9a-fA-F]+)")
PLACEHOLDER = re.compile(r"^data_(?:ov\d{3}_)?[0-9a-fA-F]{8}$")


def merge_intervals(intervals):
    merged = []
    for start, end in sorted(intervals):
        if end < start:
            raise ValueError("data range ends before it starts")
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return [(start, end) for start, end in merged]


def _contains(section, address):
    return section["start"] <= address < section["end"]


def load_data_units():
    units = {}
    for module_dir in module_dirs():
        unit = module_name(module_dir)
        path = module_dir / "delinks.txt"
        lines = path.read_text(encoding="utf-8").splitlines()
        sections = []
        claims = {name: [] for name in DATA_SECTIONS}
        in_header = True
        current_source = None

        for line in lines:
            if in_header and not line.strip():
                in_header = False
                continue
            match = SECTION_RE.match(line)
            if in_header:
                if match:
                    sections.append({
                        "name": match.group(1),
                        "start": int(match.group(2), 16),
                        "end": int(match.group(3), 16),
                    })
                continue
            source = SOURCE_RE.match(line)
            if source:
                current_source = source.group(1)
                continue
            if match:
                if current_source is None:
                    raise ValueError("%s: data claim without source: %s" % (path, line))
                claims[match.group(1)].append((int(match.group(2), 16), int(match.group(3), 16)))

        by_name = {section["name"]: section for section in sections}
        report_sections = []
        for section in sections:
            name = section["name"]
            spans = merge_intervals(claims[name])
            for start, end in spans:
                if start < section["start"] or end > section["end"]:
                    raise ValueError(
                        "%s: .%s claim 0x%x..0x%x lies outside 0x%x..0x%x"
                        % (path, name, start, end, section["start"], section["end"])
                    )
            section["matched"] = sum(end - start for start, end in spans)
            section["size"] = section["end"] - section["start"]
            section["matched_ranges"] = spans
            report_sections.append(section)

        symbols = []
        symbols_path = module_dir / "symbols.txt"
        for line in symbols_path.read_text(encoding="utf-8", errors="replace").splitlines():
            match = DATA_SYMBOL_RE.match(line)
            if not match:
                continue
            name, address = match.group(1), int(match.group(2), 16)
            section = next((item for item in report_sections if _contains(item, address)), None)
            if section is None:
                continue
            symbols.append({
                "name": name,
                "address": address,
                "section": section["name"],
                "named": not PLACEHOLDER.match(name),
            })

        units[unit] = {
            "unit": unit,
            "sections": report_sections,
            "total": sum(section["size"] for section in report_sections),
            "matched": sum(section["matched"] for section in report_sections),
            "symbols": symbols,
        }
    return units


def summarize(units):
    all_symbols = [symbol for unit in units.values() for symbol in unit["symbols"]]
    return {
        "total_data_bytes": sum(unit["total"] for unit in units.values()),
        "matched_data_bytes": sum(unit["matched"] for unit in units.values()),
        "total_data_symbols": len(all_symbols),
        "named_data_symbols": sum(1 for symbol in all_symbols if symbol["named"]),
    }


if __name__ == "__main__":
    summary = summarize(load_data_units())
    total = summary["total_data_bytes"]
    matched = summary["matched_data_bytes"]
    print("DATA: %s/%s bytes (%.2f%%), named symbols %d/%d" % (
        format(matched, ","), format(total, ","), 100.0 * matched / total if total else 100.0,
        summary["named_data_symbols"], summary["total_data_symbols"],
    ))
