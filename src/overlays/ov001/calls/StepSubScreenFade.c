#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    BOOL fadeHeld;
    BOOL fadingIn;
    u8 pad_50[0xe0 - 0x50];
    s32 brightness;
} ModeState;

extern void SetSecondaryBrightness(int brightness);

BOOL StepSubScreenFade(ModeState *state)
{
    BOOL finished = FALSE;

    if (state->fadeHeld != 0) {
        finished = TRUE;
    } else {
        if (state->fadingIn != 0) {
            state->brightness += 6;
            if (state->brightness >= 16) {
                state->brightness = 16;
                finished = TRUE;
            }
        } else {
            state->brightness -= 6;
            if (state->brightness <= -16) {
                state->brightness = -16;
                finished = TRUE;
            }
        }
        SetSecondaryBrightness(state->brightness);
    }
    return finished;
}
