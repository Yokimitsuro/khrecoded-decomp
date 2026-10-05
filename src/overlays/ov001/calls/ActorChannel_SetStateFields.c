#include "nitro/types.h"

extern u8 *data_ov001_020a0514;

void ActorChannel_SetStateFields(u32 state, u32 value1e8)
{
    u8 *ctx = data_ov001_020a0514;
    *(u32 *)(data_ov001_020a0514 + 0x98) = state;
    *(u32 *)(ctx + 0x1e8) = value1e8;
}
