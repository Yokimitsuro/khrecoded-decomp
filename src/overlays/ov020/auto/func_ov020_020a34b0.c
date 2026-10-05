#include "nitro/types.h"

u32 func_ov020_020a34b0(const void *object)
{
    return *(const u16 *)((const u8 *)object + 0x54) & 0x200;
}
