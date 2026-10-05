#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 mode;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;

void SetSoundCtxMode(u8 mode)
{
    data_ov038_020bd160->mode = mode;
    data_ov038_020bd160->flags = data_ov038_020bd160->flags | 0x4000;
}
