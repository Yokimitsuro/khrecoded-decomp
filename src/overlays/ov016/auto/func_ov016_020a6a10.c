#include "nitro/types.h"

u32 func_ov016_020a6a10(const void *object)
{
    return *(const u32 *)((const u8 *)object + 0xc0) & 0x10;
}
