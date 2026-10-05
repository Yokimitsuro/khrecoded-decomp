#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet(int bitIndex);

int CountUnlockedTiers(void)
{
    int count;

    for (count = 0; count < 8; count++) {
        if (!IsGlobalPackedBitSet(count + 0xa0b)) {
            break;
        }
    }
    return count;
}