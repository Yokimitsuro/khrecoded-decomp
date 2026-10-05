#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
} CommState;

extern CommState *gContinueSceneState;
extern s32 func_ov001_0206a814(void);

s32 ResetCommSlotWhenIdle(void)
{
    CommState *state = gContinueSceneState;

    if (func_ov001_0206a814() == 0) {
        return -1;
    }
    state->slotIndex = -1;
    gContinueSceneState->flags |= 0x8000;
    return 5;
}
