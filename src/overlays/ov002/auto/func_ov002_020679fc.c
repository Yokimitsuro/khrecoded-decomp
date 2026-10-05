#include "nitro/types.h"

extern u32 IsGlobalPackedBitSet();

u32 func_ov002_020679fc(void *object)
{
    return IsGlobalPackedBitSet((u8 *)object + 0xf50);
}
