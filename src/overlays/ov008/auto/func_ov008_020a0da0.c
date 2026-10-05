#include "nitro/types.h"

u32 func_ov008_020a0da0(const void *object)
{
    const u8 *nested = *(const u8 *const *)((const u8 *)object + 0x8);
    return *(const u32 *)(nested + 0x50);
}
