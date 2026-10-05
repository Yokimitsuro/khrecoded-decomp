#include "nitro/types.h"

extern u8 *data_ov001_020a0528;

u8 *GetStageEventRecord(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    if (index < *(u16 *)(data_ov001_020a0528 + 0x18de4)) {
        return *(u8 **)(data_ov001_020a0528 + 0x210) + index * 0x1c8;
    }
    return 0;
}
