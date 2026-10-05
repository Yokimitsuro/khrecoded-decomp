#include "nitro/types.h"

extern u8 *data_ov001_020a0528;
extern u32 CacheStageEntryValue(u32 index);

void CacheStageEntrySlot(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (data_ov001_020a0528 == 0) {
        return;
    }
    *(u32 *)(data_ov001_020a0528 + index * 0x20 + 0x18a94) = CacheStageEntryValue(index);
    *(u32 *)(data_ov001_020a0528 + index * 0x20 + 0x18ab0) = 0x99a;
}
