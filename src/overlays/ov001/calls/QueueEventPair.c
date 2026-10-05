#include "nitro/types.h"

extern u32 data_ov001_020a0490;

void QueueEventPair(u16 param1, u16 param2)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a0490;
    *(u16 *)(ctx + ctx[0x108] * 4 + 8) = param1;
    *(u16 *)(ctx + ctx[0x108] * 4 + 0xa) = param2;
    ctx[0x108] = ctx[0x108] + 1;
}
