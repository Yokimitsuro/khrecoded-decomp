#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_0000[0xc9c8];
    fx32 brightness;
    u8 pad_C9CC[0x10];
    fx32 targetBrightness;
} Ov039State;

extern Ov039State *data_ov039_020bea20;
extern void SetBrightnessAndSyncMain(int value);

void SetScreenBrightness(int brightness)
{
    Ov039State *state = data_ov039_020bea20;

    state->brightness = brightness << FX32_SHIFT;
    state->targetBrightness = brightness << FX32_SHIFT;
    SetBrightnessAndSyncMain(brightness);
}
