#!/usr/bin/env python3
"""Generate build/report.json in the objdiff report format (for decomp.dev).

Only real C (`c_decompiled_matched` in tools/audit_progress.py) counts as
matched. Units are the dsd modules; each unit is tagged with a progress
category (main, an overlay, or the library it belongs to).
"""
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import audit_progress  # noqa: E402
from project import BUILD_DIR  # noqa: E402

LIB_LABELS = {
    "nitro": "NitroSDK", "nns": "NitroSystem", "msl": "MSL", "mobiclip": "MobiClip",
}


def category_for(src_path, unit):
    if src_path:
        m = re.match(r"^libs/([^/]+)/([^/]+)/", src_path)
        if m:
            return "%s/%s" % (m.group(1), m.group(2))
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


def measures(funcs):
    total = sum(f["size"] for f in funcs)
    matched = sum(f["size"] for f in funcs if f["matched"])
    n = len(funcs)
    nm = sum(1 for f in funcs if f["matched"])
    pct = 100.0 * matched / total if total else 100.0
    # protobuf-JSON: uint64 fields are strings.
    return {
        "fuzzyMatchPercent": pct,
        "totalCode": str(total), "matchedCode": str(matched), "matchedCodePercent": pct,
        "totalData": "0", "matchedData": "0", "matchedDataPercent": 100.0,
        "totalFunctions": n, "matchedFunctions": nm,
        "matchedFunctionsPercent": 100.0 * nm / n if n else 100.0,
        "completeCode": str(matched), "completeCodePercent": pct,
        "completeData": "0", "completeDataPercent": 100.0,
    }


def build_report(functions):
    units = defaultdict(list)
    for f in functions:
        units[f["unit"]].append({
            "name": f["name"], "size": f["size"],
            "category": category_for(f.get("source"), f["unit"]),
            "matched": f["category"] == "c_decompiled_matched",
        })
    report_units, all_cats = [], set()
    for unit in sorted(units):
        funcs = sorted(units[unit], key=lambda x: x["name"])
        weight = defaultdict(int)
        for f in funcs:
            weight[f["category"]] += f["size"] or 1
            all_cats.add(f["category"])
        primary = max(weight, key=weight.get)
        report_units.append({
            "name": unit,
            "measures": measures(funcs),
            "sections": [],
            "functions": [{"name": f["name"], "size": str(f["size"]),
                           "fuzzyMatchPercent": 100.0 if f["matched"] else 0.0} for f in funcs],
            "metadata": {"moduleName": unit, "complete": all(f["matched"] for f in funcs),
                         "progressCategories": [primary]},
        })
    flat = [f for fs in units.values() for f in fs]
    aggregate = measures(flat)
    aggregate["totalUnits"] = len(report_units)
    aggregate["completeUnits"] = sum(1 for u in report_units if u["metadata"]["complete"])
    categories = [{"id": c, "name": label_for(c), "measures": measures([f for f in flat if f["category"] == c])}
                  for c in sorted(all_cats)]
    return {"measures": aggregate, "units": report_units, "version": 2, "categories": categories}


def main():
    functions, _unknown = audit_progress.classify_functions()
    report = build_report(functions)
    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "report.json").write_text(json.dumps(report, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    m = report["measures"]
    print("report.json -> %d units, %.2f%% matched code (%s/%s bytes), %d/%d functions" % (
        len(report["units"]), m["matchedCodePercent"], m["matchedCode"], m["totalCode"],
        m["matchedFunctions"], m["totalFunctions"]))


if __name__ == "__main__":
    main()
