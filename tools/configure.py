#!/usr/bin/env python3
"""Generate build.ninja for the decompilation.

Steps:
  1. regenerate every module's delinks.txt from the src/ and libs/ trees
     (tools/gen_delinks.py), merging the per-module ARM/THUMB mode fragments;
  2. `dsd delink` (original bytes for everything not yet decompiled);
  3. `dsd lcf` (linker script + object list);
  4. stage the delinked objects for the link and write build.ninja.

Then:
  ninja                  compile every matched source
  ninja build/arm9.elf   link the full ARM9 program; writes build/build/*.bin
"""
import concurrent.futures as cf
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, CONFIG_DIR, CONFIG_YAML, DSD, ROOT, module_dirs, module_name  # noqa: E402

LINK = BUILD_DIR / "link"

# Fixed addresses that no module covers, so `dsd lcf` cannot emit them. Declaring
# them linker-absolute gives the real link a definition and lets verify_idx.py
# accept the extra relocation a source takes when it references them as symbols.
ABSOLUTE_SYMBOLS = {
    # Link-time arena constants emitted as literal words in the original.
    "SDK_SYS_STACKSIZE": 0,
    "SDK_SECTION_ARENA_DTCM_START": 0x027E0280,
    # Size reserved for the IRQ stack in DTCM.
    "SDK_IRQ_STACKSIZE": 0x800,
    # Inter-processor lock word at the top of main RAM.
    "data_027ffff0": 0x027FFFF0,
    # Cartridge module information cached in the shared system work area.
    "data_02fffc30": 0x02FFFC30,
    # Game state pointer stored in the shared system work area.
    "gEngineState": 0x02FFFC20,
    # VBlank counter mixed into wireless timing dispersion.
    "gVBlankCount": 0x02FFFC3C,
    # Shared wireless request flags written by ARM7.
    "data_02ffff96": 0x02FFFF96,
    # Fixed overlay ID used by the save-system self-check.
    "gSaveCheckOverlayId": 0x68,
    # Storage immediately before OSi_ArenaState used by the idle thread.
    "OSi_IdleThreadStack": 0x02056CFC,
    # Save verification callbacks execute from overlay 104 but are referenced
    # directly by the resident ARM9 initialization path.
    "__DSProt_DetectNotFlashcart": 0x020D1EFC,
    "__DSProt_DetectEmulator": 0x020D1F38,
    "__DSProt_DetectNotDummy": 0x020D1FEC,
    # Camera vectors live inside the main-module BSS rather than a compiled
    # translation unit, but recovered C references the structure by name.
    "NNS_G3dGlb_camPos": 0x0205AB3C,
}


def discover_modules():
    return [d for d in module_dirs() if (d / "delinks.txt").exists()]


MODULES = discover_modules()


def files_from_delinks(delinks_txt):
    """Source paths declared as FILE entries in a delinks.txt."""
    out = []
    for line in delinks_txt.read_text(encoding="utf-8").splitlines():
        if line.endswith(":") and "/" in line and not line.startswith(" "):
            out.append(line[:-1])
    return out


def stage_delinked_objects(link_dir, compiled_names=()):
    """Copy the dsd delink objects into build/link/ with flat names.

    `dsd lcf` references bare object names, so mwldarm finds them via the
    staging directory. A delink whose source we compile is not staged: two
    objects with the same bare name would leave the choice to input order.
    """
    compiled_names = set(compiled_names)
    for stale in compiled_names:
        f = link_dir / stale
        if f.exists():
            f.unlink()
    skipped = 0
    for src in (BUILD_DIR / "delinks").rglob("*.o"):
        if src.name in compiled_names:
            skipped += 1
            continue
        dst = link_dir / src.name
        if dst.exists() and dst.stat().st_mtime >= src.stat().st_mtime:
            continue
        shutil.copyfile(src, dst)
    if skipped:
        print(f"[configure] staged delinks, skipped {skipped} superseded by compiled sources")


def rel(p):
    """Path relative to ROOT, posix, ninja-safe (the project path may contain spaces)."""
    return Path(p).resolve().relative_to(ROOT).as_posix()


def source_rule(source):
    suffix = Path(source).suffix.lower()
    if suffix in (".c", ".cpp"):
        return "mwcc"
    if suffix in (".s", ".asm"):
        return "armasm"
    raise ValueError(f"unsupported source type: {source}")


def emit_ninja(ninja_path, src_files):
    py = sys.executable.replace("\\", "/")
    lines = [
        "ninja_required_version = 1.10",
        "",
        f"python = {py}",
        "",
        "rule mwcc",
        # Mode and compiler override travel on the command line so a flip of
        # either recompiles exactly that file.
        "  command = $python tools/_run_mwcc.py $out $in --mode=$mode --cc=$cc",
        "  description = MWCC $in",
        "  restat = 1",
        "",
        "rule armasm",
        "  command = $python tools/_run_armasm.py $out $in",
        "  description = ARMASM $in",
        "  restat = 1",
        "",
        "rule mwld",
        "  command = $python tools/_run_mwld.py $out $lcf $out.rsp",
        "  description = MWLD $out",
        "  rspfile = $out.rsp",
        "  rspfile_content = $rspcontent",
        "",
    ]

    compiled_objs = []
    modes_path = BUILD_DIR / "file_modes.json"
    modes = json.loads(modes_path.read_text(encoding="utf-8")) if modes_path.exists() else {}
    comp_path = BUILD_DIR / "file_compilers.json"
    cmap = json.loads(comp_path.read_text(encoding="utf-8")) if comp_path.exists() else {}
    for src in src_files:
        obj_path = BUILD_DIR / Path(src).with_suffix(".o")
        obj_path.parent.mkdir(parents=True, exist_ok=True)
        obj = rel(obj_path)
        compiled_objs.append(obj)
        if source_rule(src) == "mwcc":
            lines.append(f"build {obj}: mwcc {src}")
            lines.append(f"  mode = {modes.get(src, 'arm')}")
            lines.append(f"  cc = {cmap.get(src) or 'default'}")
        else:
            lines.append(f"build {obj}: armasm {src}")

    lines.append("")
    lines.append("build compile: phony " + " ".join(compiled_objs))
    lines.append("")

    all_link_inputs = list(compiled_objs)
    compiled_set = set(compiled_objs)
    for p in sorted(LINK.glob("*.o")):
        rp = rel(p)
        if rp not in compiled_set:
            all_link_inputs.append(rp)

    lcf = rel(BUILD_DIR / "arm9.lcf")
    # mwldarm resolves the LCF's `> build/*.bin` redirects relative to the ELF,
    # so the module images land in build/build/, where config.yaml expects them.
    elf_out = rel(BUILD_DIR / "arm9.elf")
    lines.append(f"build {elf_out}: mwld {' '.join(compiled_objs)} | {lcf}")
    lines.append(f"  lcf = {lcf}")
    lines.append(f"  rspcontent = {' '.join(all_link_inputs)}")
    lines.append("")
    lines.append("default compile")
    lines.append("")

    ninja_path.write_text("\n".join(lines), encoding="utf-8", newline="\n")


def add_absolute_symbols(lcf_path):
    """Append the linker-absolute symbols to the SECTIONS block dsd generated."""
    text = lcf_path.read_text(encoding="utf-8")
    wanted = ["    %s = 0x%08X;" % (name, addr) for name, addr in sorted(ABSOLUTE_SYMBOLS.items())]
    missing = [line for line in wanted if line not in text]
    if not missing:
        return
    marker = "SECTIONS {\n"
    idx = text.index(marker) + len(marker)
    text = text[:idx] + "\n".join(missing) + "\n" + text[idx:]
    lcf_path.write_text(text, encoding="utf-8", newline="\n")
    print("[configure] added %d absolute symbol(s) to the LCF" % len(missing))


def run(*cmd):
    # On some Windows setups a child occasionally dies with no output at all
    # (an external process interfering with file access). Retry only that exact
    # signature; anything that printed a diagnostic is a real error.
    for _ in range(4):
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode == 0 or r.stdout.strip() or r.stderr.strip():
            break
        print(f"[configure] retrying (rc={r.returncode}, no output): {cmd[-1]}")
    if r.returncode != 0:
        print(r.stdout)
        print(r.stderr, file=sys.stderr)
        raise SystemExit(f"failed (rc={r.returncode}): {' '.join(str(c) for c in cmd)}")
    return r


def write_if_changed(path, text):
    if not path.exists() or path.read_text(encoding="utf-8") != text:
        path.write_text(text, encoding="utf-8", newline="\n")


def main():
    LINK.mkdir(parents=True, exist_ok=True)
    (BUILD_DIR / "build").mkdir(parents=True, exist_ok=True)

    # Per-file compiler overrides (config/arm9/file_compilers.json maps a source
    # path to a tools/mwccarm/<version> directory). Always written so the build
    # can rely on it.
    src_compilers = CONFIG_DIR / "file_compilers.json"
    compilers_text = src_compilers.read_text(encoding="utf-8") if src_compilers.exists() else "{}\n"
    write_if_changed(BUILD_DIR / "file_compilers.json", compilers_text)

    if "--skip-delinks" in sys.argv:
        print("[configure] preserving existing delinks.txt files (--skip-delinks)")
    else:
        gen = str(ROOT / "tools" / "gen_delinks.py")
        workers = min(len(MODULES), os.cpu_count() or 4)
        print(f"[configure] regen delinks.txt for {len(MODULES)} modules ({workers} at a time)")
        with cf.ThreadPoolExecutor(max_workers=workers) as pool:
            list(pool.map(lambda d: run(sys.executable, gen, str(d)), MODULES))

    # Merge the per-module mode fragments in module order.
    frags = [BUILD_DIR / "file_modes.d" / (module_name(m) + ".json") for m in MODULES]
    all_modes = {}
    for f in frags:
        if f.exists():
            all_modes.update(json.loads(f.read_text(encoding="utf-8")))
    write_if_changed(BUILD_DIR / "file_modes.json", json.dumps(all_modes, indent=2, sort_keys=True))
    print(f"[configure] file_modes.json: {len(all_modes)} entries")

    print("[configure] dsd delink")
    run(str(DSD), "delink", "--config-path", str(CONFIG_YAML))
    print("[configure] dsd lcf")
    run(str(DSD), "lcf", "--config-path", str(CONFIG_YAML))
    add_absolute_symbols(BUILD_DIR / "arm9.lcf")

    src_files = []
    for module_dir in MODULES:
        src_files.extend(files_from_delinks(module_dir / "delinks.txt"))
    src_files = sorted(set(src_files))
    print(f"[configure] {len(src_files)} matched source files to compile")

    print("[configure] stage delinked objects into build/link/")
    stage_delinked_objects(LINK, {Path(s).with_suffix(".o").name for s in src_files})

    emit_ninja(ROOT / "build.ninja", src_files)
    print("[configure] wrote build.ninja")


if __name__ == "__main__":
    main()
