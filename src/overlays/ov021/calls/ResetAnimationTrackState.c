#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x0F];
    s16 scale;
    u8 pad_12[0x02];
    s32 rate;
    u8 pad_18[0x10];
    s16 prevIndex;
    s16 index;
} TrackState;

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

void ResetAnimationTrackState(TrackState *state)
{
    MI_CpuFill8(state, 0, sizeof(TrackState));
    state->id = 0xff;
    state->scale = 0x1000;
    state->index = -1;
    state->prevIndex = state->index;
    state->rate = 0x1000;
}
