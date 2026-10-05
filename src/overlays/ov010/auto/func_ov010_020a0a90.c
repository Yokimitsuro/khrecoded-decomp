#include "nitro/types.h"

u32 func_ov010_020a0a90(const void *object)
{
    const u8 *nested = *(const u8 *const *)((const u8 *)object + 0x8);
    return *(const u32 *)(nested + 0x50);
}
