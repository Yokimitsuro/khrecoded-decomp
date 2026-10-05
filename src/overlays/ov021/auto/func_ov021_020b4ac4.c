#include "nitro/types.h"

void *func_ov021_020b4ac4(const void *object, u32 index)
{
    u8 *base = *(u8 *const *)((const u8 *)object + 0xc);
    return base + index;
}
