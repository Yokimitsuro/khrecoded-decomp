#include "nitro/types.h"

typedef struct SlotValues {
    u8 pad_0000[0x24e0];
    s16 values[0x76a];
    u32 count;
} SlotValues;

typedef struct UnlockFlags {
    u8 pad_0000[0x2d38];
    u32 mask;
} UnlockFlags;

extern SlotValues *gMapLayout;
extern UnlockFlags *data_0205fe0c;

int GetUnlockedSlotValue(u32 index)
{
    SlotValues *slots = gMapLayout;
    int result = -1;

    if (index < slots->count && (data_0205fe0c->mask & (1 << index))) {
        result = slots->values[index];
    }
    return result;
}
