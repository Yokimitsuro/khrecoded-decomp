#include "nitro/types.h"

extern u32 data_ov001_020a0490;

void ClearQueueFlag(void)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a0490;
    *(s8 *)(ctx + 6) = -1;
}
