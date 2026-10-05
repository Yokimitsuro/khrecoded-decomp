#include "nitro/types.h"

extern void WriteGlobalPackedBits(s32 recordId, s32 index, s32 value);

void SetClampedPercentValue(s32 value) {
    if (value < 0) {
        value = 0;
    } else if (100 < value) {
        value = 100;
    }
    WriteGlobalPackedBits(0x9f0, 7, value);
}
