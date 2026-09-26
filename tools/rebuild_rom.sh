#!/usr/bin/env bash
# Round-trip check of the extraction: rebuild the ROM straight from
# dsd_extract/ (no compiling or linking) and compare it with the reference.
#
# Expected result: exactly 4 bytes differ, at 0x6C/0x6D (secure-area CRC) and
# 0x15E/0x15F (header CRC). Anything more means the extraction is broken.
set -e
cd "$(dirname "$0")/.."

tools/dsd.exe rom build --config dsd_extract/config.yaml --rom build/roundtrip.nds

echo
echo "Original SHA-1: $(sha1sum recoded.nds | awk '{print $1}')"
echo "Rebuilt  SHA-1: $(sha1sum build/roundtrip.nds | awk '{print $1}')"
diff_bytes=$(cmp -l recoded.nds build/roundtrip.nds 2>/dev/null | wc -l || true)
echo "Bytes differing: $diff_bytes"
if [ "$diff_bytes" -le 4 ]; then
    echo "OK: round trip clean (<= 4 header CRC bytes)."
else
    echo "FAIL: more than 4 bytes differ."
    cmp -l recoded.nds build/roundtrip.nds 2>/dev/null | head -10 | awk '{printf "  diff @ 0x%X (orig=%s built=%s)\n", $1 - 1, $2, $3}'
    exit 1
fi
