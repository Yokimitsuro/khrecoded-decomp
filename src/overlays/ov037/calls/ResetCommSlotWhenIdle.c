#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
} CommState;

extern CommState *gContinueSceneState;
extern s32 IsScreenModeIdle(void);

s32 ResetCommSlotWhenIdle(void)
{
    CommState *state = gContinueSceneState;

    if (IsScreenModeIdle() == 0) {
        return -1;
    }
    state->slotIndex = -1;
    gContinueSceneState->flags |= 0x8000;
    return 5;
}
