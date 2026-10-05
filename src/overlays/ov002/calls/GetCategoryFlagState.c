#pragma optimization_level 3
#include "nitro/types.h"

typedef struct RecordFlagSets {
    u8 primaryBits[0x67];
    u8 secondaryBits[0x67];
} RecordFlagSets;

extern u8 data_ov002_0206ada0[];
extern u16 data_ov002_0206adb4[];

s32 GetCategoryFlagState(RecordFlagSets *flagSets, s32 bitIndex) {
    s32 byteIndex;
    s32 endBit;
    s32 recordCount;
    s32 result;
    u8 mask;

    if (bitIndex < 0) {
        for (byteIndex = 0; byteIndex < 0x67; byteIndex++) {
            if (flagSets->secondaryBits[byteIndex] != 0) {
                return 1;
            }
        }
        return 0;
    }
    recordCount = data_ov002_0206ada0[bitIndex];
    if (recordCount == 0) {
        return 0;
    }
    bitIndex = data_ov002_0206adb4[bitIndex];
    result = 0;
    endBit = recordCount + bitIndex;
    for (; bitIndex < endBit; bitIndex++) {
        byteIndex = bitIndex >> 3;
        mask = 1 << (u8)(bitIndex - (byteIndex << 3));
        if (mask & flagSets->secondaryBits[byteIndex]) {
            if (mask & flagSets->primaryBits[byteIndex]) {
                return 1;
            }
            result = -1;
        }
    }
    return result;
}
