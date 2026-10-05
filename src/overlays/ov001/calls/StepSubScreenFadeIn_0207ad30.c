#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    s32 phase;
    u8 pad_34[0x58 - 0x34];
    s32 fadeSpeed;
    u8 pad_5c[0xe0 - 0x5c];
    s32 brightness;
} ModeState;

extern void SetSecondaryBrightness(int brightness);

void StepSubScreenFadeIn_0207ad30(ModeState *state)
{
    state->brightness -= state->fadeSpeed;
    if (state->brightness <= 0) {
        state->brightness = 0;
        state->phase = 6;
    }
    SetSecondaryBrightness(state->brightness);
}
