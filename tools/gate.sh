#!/usr/bin/env bash
# Full module gate: every linked module must be byte-identical to the ROM.
#
#   bash tools/gate.sh
#
# Order matters. `dsd check modules` only hashes build/build/*.bin, so the
# previous binaries are deleted first and only the real link below can write
# them again: a failed compile or link leaves them missing and the check fails
# instead of passing on stale output.
set -euo pipefail

cd "$(dirname "$0")/.."

echo "== 1/6 file name vs defined symbol"
python tools/audit_symbol_names.py

echo "== 2/6 remove the previous link output"
rm -f build/build/arm9.bin build/build/itcm.bin build/build/dtcm.bin build/build/arm9_ov*.bin

echo "== 3/6 configure"
python tools/configure.py

echo "== 4/6 compile"
ninja

echo "== 5/6 link (writes build/build/*.bin, repairs interworking)"
ninja build/arm9.elf

echo "== 6/6 dsd check modules"
expected=$(python -c "import sys; sys.path.insert(0, 'tools'); import project; print(project.module_count())")
out=$(tools/dsd.exe check modules --config-path config/arm9/config.yaml -f 2>&1 || true)
ok=$(printf '%s\n' "$out" | grep -c ": OK" || true)
echo "modules OK: $ok / $expected"
if [ "$ok" != "$expected" ]; then
    printf '%s\n' "$out" | grep -v ": OK" | head -40
    echo "GATE FAILED"
    exit 1
fi
echo "GATE PASSED ($ok/$expected linked modules byte-exact)"
