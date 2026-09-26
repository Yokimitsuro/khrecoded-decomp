"""Project-wide constants shared by the tools.

Everything that identifies the target ROM or the toolchain lives here so the
individual scripts do not each carry their own copy.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Reference dump (see CONTRIBUTING.md for the hashes).
ROM = ROOT / "recoded.nds"
GAME_CODE = "BK9P"
GAME_TITLE = "Kingdom Hearts Re:coded"
BUILT_ROM = ROOT / "build" / "recoded.nds"

# Toolchain. Contributors provide these themselves; none of them is tracked.
DSD = ROOT / "tools" / "dsd.exe"
MWCC_DIR = ROOT / "tools" / "mwccarm"
MWCCARM = MWCC_DIR / "3.0_patch4" / "mwccarm.exe"
MWLDARM = MWCC_DIR / "2.0" / "sp2p4" / "mwldarm.exe"
LICENSE = MWCC_DIR / "license.dat"

CONFIG_DIR = ROOT / "config" / "arm9"
CONFIG_YAML = CONFIG_DIR / "config.yaml"
EXTRACT_DIR = ROOT / "dsd_extract"
BUILD_DIR = ROOT / "build"
FUNC_INDEX = BUILD_DIR / "func_index.json"

# mwccarm 3.0 build 139 (CodeWarrior for DS 2.0 SP2 patch 4).
CFLAGS = [
    "-O4,p", "-proc", "arm946e", "-interworking",
    "-lang", "c99", "-enum", "int", "-char", "signed",
    "-inline", "on,noauto", "-Cpp_exceptions", "off", "-gccext,on",
]


def module_dirs():
    """Every dsd module config directory, main first, then autoloads and overlays."""
    out = [CONFIG_DIR]
    for name in ("itcm", "dtcm"):
        if (CONFIG_DIR / name).is_dir():
            out.append(CONFIG_DIR / name)
    ov_root = CONFIG_DIR / "overlays"
    if ov_root.is_dir():
        out.extend(sorted(p for p in ov_root.iterdir() if p.is_dir()))
    return out


def module_name(module_dir):
    """config/arm9 -> main, config/arm9/itcm -> itcm, .../overlays/ov006 -> ov006."""
    rel = Path(module_dir).resolve().relative_to(CONFIG_DIR)
    return "main" if rel == Path(".") else rel.parts[-1]


def module_count():
    """Number of modules declared in config.yaml (main + autoloads + overlays)."""
    text = CONFIG_YAML.read_text(encoding="utf-8")
    return len(re.findall(r"^\s+(?:-\s+)?object:", text, re.M))
