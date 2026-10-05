#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x19c];
    u32 animationFinished;
} Panel;

extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);

s32 WaitForAnimationFinish(Panel *panel)
{
    s32 nextState = -1;

    if (panel->animationFinished != 0) {
        SetPanelState(panel, 0, 0x1e, 0);
        nextState = 5;
    }
    return nextState;
}
