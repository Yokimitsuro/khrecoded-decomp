#include "nitro/types.h"

void *func_ov001_02086384(const void *object, u32 index)
{
    u8 *base = *(u8 *const *)((const u8 *)object + 0x40);
    u16 stride = *(const u16 *)((const u8 *)object + 0x3c);
    return base + stride * index;
}
