#include "nitro/types.h"

extern void SetPackedBit(int *bitWords, int bitIndex);
extern u8 *data_ov095_020c28e0;

void SetEntryFlag_020c1374(int useSecondSet, int bitIndex)
{
    u8 *base = data_ov095_020c28e0;
    if (useSecondSet == 0) {
        base += 0x124;
    } else {
        base += 0x144;
    }
    SetPackedBit((int *)(base + 0x11000), bitIndex);
}
