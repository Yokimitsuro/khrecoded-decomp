#include "nitro/types.h"

extern u8 *data_ov001_020a0528;

u8 *GetStageEntrySlot(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    if (index < 0x40) {
        return data_ov001_020a0528 + 0x18b78 + index * 8;
    }
    return 0;
}
