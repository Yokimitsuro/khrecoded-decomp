#!/usr/bin/env python3
"""Generate build/report.json in the objdiff report format for decomp.dev.

Code only counts when a real C source is classified as byte-exact. DATA totals
come from each module's section table; matched DATA comes only from source-owned
ranges retained in delinks.txt after byte-exact verification.
"""
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import audit_progress  # noqa: E402
import data_progress  # noqa: E402
from project import BUILD_DIR  # noqa: E402

LIB_LABELS = {
    "nitro": "NitroSDK", "nns": "NitroSystem", "msl": "MSL", "mobiclip": "MobiClip",
}


def category_for(src_path, unit):
    if src_path:
        match = re.match(r"^libs/([^/]+)/([^/]+)/", src_path)
        if match:
            return "%s/%s" % (match.group(1), match.group(2))
    if unit.startswith("ov"):
        return "overlays/" + unit
    return "main"


def label_for(cid):
    if cid == "main":
        return "Main + ITCM + DTCM"
    if cid.startswith("overlays/ov"):
        return "Overlay " + cid.split("/ov", 1)[1]
    lib, _, mod = cid.partition("/")
    return "%s: %s" % (LIB_LABELS.get(lib, lib), mod)


def measures(funcs, total_data=0, matched_data=0):
    total_code = sum(func["size"] for func in funcs)
    matched_code = sum(func["size"] for func in funcs if func["matched"])
    function_count = len(funcs)
    matched_functions = sum(1 for func in funcs if func["matched"])
    code_percent = 100.0 * matched_code / total_code if total_code else 100.0
    data_percent = 100.0 * matched_data / total_data if total_data else 100.0
    total_size = total_code + total_data
    fuzzy_percent = 100.0 * (matched_code + matched_data) / total_size if total_size else 100.0
    return {
        "fuzzyMatchPercent": fuzzy_percent,
        "totalCode": str(total_code),
        "matchedCode": str(matched_code),
        "matchedCodePercent": code_percent,
        "totalData": str(total_data),
        "matchedData": str(matched_data),
        "matchedDataPercent": data_percent,
        "totalFunctions": function_count,
        "matchedFunctions": matched_functions,
        "matchedFunctionsPercent": (
            100.0 * matched_functions / function_count if function_count else 100.0
        ),
        "completeCode": str(matched_code),
        "completeCodePercent": code_percent,
        "completeData": str(matched_data),
        "completeDataPercent": data_percent,
    }


def report_sections(data):
    out = []
    for section in data["sections"]:
        if not section["size"]:
            continue
        out.append({
            "name": "." + section["name"],
            "size": str(section["size"]),
            "fuzzyMatchPercent": 100.0 * section["matched"] / section["size"],
            "metadata": {"virtualAddress": str(section["start"])},
        })
    return out


def build_report(functions, data_units=None):
    if data_units is None:
        data_units = data_progress.load_data_units()

    units = defaultdict(list)
    for func in functions:
        units[func["unit"]].append({
            "name": func["name"],
            "size": func["size"],
            "category": category_for(func.get("source"), func["unit"]),
            "matched": func["category"] == "c_decompiled_matched",
        })

    report_units = []
    all_categories = set()
    category_data = defaultdict(lambda: [0, 0])
    for unit in sorted(set(units) | set(data_units)):
        funcs = sorted(units[unit], key=lambda item: item["name"])
        data = data_units.get(unit, {"sections": [], "total": 0, "matched": 0})
        weight = defaultdict(int)
        for func in funcs:
            weight[func["category"]] += func["size"] or 1
            all_categories.add(func["category"])
        primary = max(weight, key=weight.get) if weight else category_for(None, unit)

        data_category = category_for(None, unit)
        category_data[data_category][0] += data["total"]
        category_data[data_category][1] += data["matched"]
        if data["total"]:
            all_categories.add(data_category)

        unit_measures = measures(funcs, data["total"], data["matched"])
        report_units.append({
            "name": unit,
            "measures": unit_measures,
            "sections": report_sections(data),
            "functions": [
                {
                    "name": func["name"],
                    "size": str(func["size"]),
                    "fuzzyMatchPercent": 100.0 if func["matched"] else 0.0,
                }
                for func in funcs
            ],
            "metadata": {
                "moduleName": unit,
                "complete": (
                    all(func["matched"] for func in funcs)
                    and data["matched"] == data["total"]
                ),
                "progressCategories": [primary],
            },
        })

    flat = [func for funcs in units.values() for func in funcs]
    total_data = sum(data["total"] for data in data_units.values())
    matched_data = sum(data["matched"] for data in data_units.values())
    aggregate = measures(flat, total_data, matched_data)
    aggregate["totalUnits"] = len(report_units)
    aggregate["completeUnits"] = sum(
        1 for unit in report_units if unit["metadata"]["complete"]
    )

    categories = []
    for category in sorted(all_categories):
        category_funcs = [func for func in flat if func["category"] == category]
        data_total, data_matched = category_data[category]
        categories.append({
            "id": category,
            "name": label_for(category),
            "measures": measures(category_funcs, data_total, data_matched),
        })
    return {
        "measures": aggregate,
        "units": report_units,
        "version": 2,
        "categories": categories,
    }


def validate_report(report):
    aggregate = report["measures"]
    unit_data = sum(int(unit["measures"]["totalData"]) for unit in report["units"])
    unit_matched = sum(int(unit["measures"]["matchedData"]) for unit in report["units"])
    if unit_data != int(aggregate["totalData"]):
        raise ValueError("unit DATA totals do not match the aggregate")
    if unit_matched != int(aggregate["matchedData"]):
        raise ValueError("unit matched DATA does not match the aggregate")
    for unit in report["units"]:
        section_total = sum(int(section["size"]) for section in unit["sections"])
        if section_total != int(unit["measures"]["totalData"]):
            raise ValueError("%s: section DATA total does not match unit" % unit["name"])


def main():
    functions, _unknown = audit_progress.classify_functions()
    report = build_report(functions)
    validate_report(report)
    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "report.json").write_text(
        json.dumps(report, indent=1, sort_keys=True) + "\n", encoding="utf-8"
    )
    values = report["measures"]
    print(
        "report.json -> %d units, %.2f%% matched code (%s/%s bytes), "
        "%.2f%% matched DATA (%s/%s bytes), %d/%d functions"
        % (
            len(report["units"]),
            values["matchedCodePercent"], values["matchedCode"], values["totalCode"],
            values["matchedDataPercent"], values["matchedData"], values["totalData"],
            values["matchedFunctions"], values["totalFunctions"],
        )
    )


if __name__ == "__main__":
    main()
