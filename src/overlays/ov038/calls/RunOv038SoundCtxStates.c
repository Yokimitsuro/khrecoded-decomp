#include "nitro/types.h"

typedef s32 (*SoundCtxStateFunc)(void);

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x0c];
    s32 state;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;
extern SoundCtxStateFunc gResultsSoundStateHandlers[];

u32 RunOv038SoundCtxStates(void)
{
    s32 nextState;

    do {
        data_ov038_020bd160->flags &= 0x7fff;
        nextState = gResultsSoundStateHandlers[data_ov038_020bd160->state]();
        if (nextState >= 0) {
            data_ov038_020bd160->state = nextState;
        }
    } while (data_ov038_020bd160->flags & 0x8000);
    return 0;
}
