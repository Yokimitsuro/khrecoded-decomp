#include "nitro/types.h"

extern u8 *data_ov001_020a0528;
extern s32 func_ov001_0206dc38(u32 scaledIndex);
extern u32 GetBoundedEntryField(u32 index);

u32 CacheStageEntryValue(u32 id)
{
    u32 scaled = (id - 1) * 0x10000;
    u32 index = scaled >> 16;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    if ((s32)index < func_ov001_0206dc38(scaled)) {
        *(u32 *)(data_ov001_020a0528 + index * 0x20 + 0x18a94) = GetBoundedEntryField(index);
        return *(u32 *)(data_ov001_020a0528 + index * 0x20 + 0x18a94);
    }
    return 0;
}
