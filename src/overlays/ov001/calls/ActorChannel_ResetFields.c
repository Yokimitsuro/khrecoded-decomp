#include "nitro/types.h"

extern u8 *data_ov001_020a0514;
extern void Obj_ReleaseIfSet(void *channel);

void ActorChannel_ResetFields(void)
{
    u8 *ctx = data_ov001_020a0514;
    Obj_ReleaseIfSet(ctx + 0x140);
    *(s32 *)(ctx + 0x1e4) = 0;
    *(s32 *)(ctx + 0x1e8) = 0;
    *(s32 *)(ctx + 0x1ec) = 0;
    *(s32 *)(ctx + 0x98) = 0;
}
