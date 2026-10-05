#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xCB88];
    s32 phase;
    s32 step;
    s32 timer;
} Ov103State;

void SetScenePhase(s32 phase, Ov103State *state)
{
    state->phase = phase;
    state->step = 0;
    state->timer = 0;
}
