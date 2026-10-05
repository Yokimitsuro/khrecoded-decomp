#include "nitro/types.h"

#define GLOBAL_FLAG_BANK_BASE 0xf50

extern void SetGlobalPackedBit(int bitIndex);
extern void ClearGlobalPackedBit(int bitIndex);

void WriteGlobalPackedFlag(int flagIndex, BOOL enabled)
{
    if (enabled) {
        SetGlobalPackedBit(flagIndex + GLOBAL_FLAG_BANK_BASE);
        return;
    }
    ClearGlobalPackedBit(flagIndex + GLOBAL_FLAG_BANK_BASE);
}
