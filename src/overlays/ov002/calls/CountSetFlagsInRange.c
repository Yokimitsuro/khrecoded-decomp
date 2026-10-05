#include "nitro/types.h"

extern s32 IsGlobalPackedBitSet(s32 flagId);

s32 CountSetFlagsInRange(void) {
    s32 count = 0;
    s32 index = 0;
    s32 result;

    do {
        result = IsGlobalPackedBitSet(index + 0xf1a);
        index = index + 1;
        if (result != 0) {
            count = count + 1;
        }
    } while (index < 0x1e);
    return count;
}
