#include "nitro/types.h"

extern u8 *data_ov001_020a0514;

void ActorChannel_QueueRequest(u32 param1, u32 param2)
{
    u8 *ctx = data_ov001_020a0514;
    *(u32 *)(data_ov001_020a0514 + 0x8c) = *(u32 *)(data_ov001_020a0514 + 0x84);
    *(u32 *)(ctx + 0x84) = param2;
    *(u32 *)(ctx + 0x90) = param1;
    *(u32 *)(ctx + 0x94) = *(u32 *)(ctx + 0x90);
    *(u32 *)(ctx + 0x98) = 7;
}
