#include "nitro/types.h"

extern void ClearPackedBit(int *bitWords, int bitIndex);
extern u8 *data_ov095_020c28e0;

void ClearEntryFlag_020c139c(int useSecondSet, int bitIndex)
{
    u8 *base = data_ov095_020c28e0;
    if (useSecondSet == 0) {
        base += 0x124;
    } else {
        base += 0x144;
    }
    ClearPackedBit((int *)(base + 0x11000), bitIndex);
}
