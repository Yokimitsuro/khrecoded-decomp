#include "nitro/types.h"

extern u32 WriteSessionPackedBits(u32 slotId, u32 size, u32 value);

u32 ClearFixedSlots(void) {
    s32 index = 0;
    do {
        WriteSessionPackedBits(index * 2 + 0x331f, 2, 0);
        index = index + 1;
    } while (index < 0x100);
    WriteSessionPackedBits(0x3880, 0x660, 0);
    return 1;
}
