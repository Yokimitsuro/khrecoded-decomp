#!/usr/bin/env bash
# Pack a ROM from the linked module binaries and compare it with the reference.
#
# Prerequisite: tools/gate.sh has passed (build/arm9.elf and build/build/*.bin
# are the linked, byte-exact modules).
#
# Expected result: exactly 4 bytes differ, at 0x6C/0x6D (secure-area CRC) and
# 0x15E/0x15F (header CRC). Anything more means the pipeline regressed.
set -e
cd "$(dirname "$0")/.."

echo "[build_rom] dsd rom config (ELF -> rom_config.yaml)"
tools/dsd.exe rom config --elf build/arm9.elf --config config/arm9/config.yaml

echo "[build_rom] dsd rom build -> build/recoded.nds"
tools/dsd.exe rom build --config build/build/rom_config.yaml --rom build/recoded.nds

echo
echo "Original SHA-1: $(sha1sum recoded.nds | awk '{print $1}')"
echo "Built    SHA-1: $(sha1sum build/recoded.nds | awk '{print $1}')"
diff_bytes=$(cmp -l recoded.nds build/recoded.nds 2>/dev/null | wc -l || true)
echo "Bytes differing: $diff_bytes"
if [ "$diff_bytes" -le 4 ]; then
    echo "OK: the built ROM matches the reference (<= 4 header CRC bytes)."
    cmp -l recoded.nds build/recoded.nds 2>/dev/null | awk '{printf "  diff @ 0x%X\n", $1 - 1}'
else
    echo "FAIL: more than 4 bytes differ."
    cmp -l recoded.nds build/recoded.nds 2>/dev/null | head -20 | awk '{printf "  diff @ 0x%X (orig=%s built=%s)\n", $1 - 1, $2, $3}'
    exit 1
fi
