#include "nitro/types.h"

u8 func_ov006_020a14e0(const void *object, u32 index)
{
    const u8 *table = *(const u8 *const *)((const u8 *)object + 0x24);
    return table[index * 4];
}
