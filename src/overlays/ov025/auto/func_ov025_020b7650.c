#include "nitro/types.h"

u16 func_ov025_020b7650(const void *table, u32 index)
{
    const u8 *entry = *(const u8 *const *)((const u8 *)table + index * 4 + 0x70);
    return *(const u16 *)(entry + 4);
}
