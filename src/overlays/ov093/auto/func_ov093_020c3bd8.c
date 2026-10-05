#include "nitro/types.h"

u32 func_ov093_020c3bd8(const void *object, u32 mask)
{
    return *(const u32 *)((const u8 *)object + 4) & mask;
}
