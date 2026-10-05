#include "nitro/types.h"

u32 func_ov017_020a5dfc(const void *object)
{
    return *(const u16 *)((const u8 *)object + 0x54) & 0x4;
}
