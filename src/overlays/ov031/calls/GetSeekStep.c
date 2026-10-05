#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    s32 position;
    u8 pad_2c[0x4];
    s32 target;
    s32 step;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

s32 GetSeekStep(void)
{
    OverlayState *state = data_ov031_020bc820;
    s32 diff = state->target - state->position;
    s32 sign;

    if (diff == 0) {
        sign = 0;
    } else if (diff > 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    return state->step * sign;
}
