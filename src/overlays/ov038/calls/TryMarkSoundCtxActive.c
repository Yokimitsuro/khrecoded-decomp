#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;
extern u32 func_ov001_02063620(void);

u32 TryMarkSoundCtxActive(void)
{
    u32 result;

    result = func_ov001_02063620();
    if (result == 0) {
        data_ov038_020bd160->flags = data_ov038_020bd160->flags | 0x8000;
        return 1;
    }
    return 0xffffffff;
}
