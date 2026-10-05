#include "nitro/types.h"

typedef struct SoundCtx {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;

s32 MarkSoundCtxRepeatIfReady(void)
{
    SoundCtx *ctx = data_ov038_020bd160;

    if (ctx->flags & 0x4000) {
        ctx->flags |= 0x8000;
        return 4;
    }
    return -1;
}
