#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;

BOOL IsOv038SoundCtxFlag0Clear(void)
{
    if (data_ov038_020bd160 == NULL) {
        return FALSE;
    }
    if ((data_ov038_020bd160->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
