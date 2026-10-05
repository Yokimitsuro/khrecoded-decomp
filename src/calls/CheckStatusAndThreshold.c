#include "nitro/types.h"

extern s32 GetBit26Flag(void);
extern s32 GetSlotFlagsField(void);

s32 CheckStatusAndThreshold(void)
{
    if (GetBit26Flag() == 0 && GetSlotFlagsField() >= 0x50) {
        return 2;
    }
    return 1;
}
