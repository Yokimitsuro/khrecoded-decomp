#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FadeState {
    u32 flags;
    u8 pad_04[4];
    fx32 mainBrightness;
    fx32 subBrightness;
    u8 pad_10[0xc];
    fx32 step;
} FadeState;

extern FadeState *data_ov001_020a04a0;
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void func_ov001_0206a138();

void *StepBrightnessFade(void)
{
    FadeState *fade = data_ov001_020a04a0;

    if (fade->flags & 0x20) {
        return NULL;
    }
    SetBrightnessAndSyncMain(fade->mainBrightness >> 12);
    SetSecondaryBrightness(fade->subBrightness >> 12);
    if (fade->flags & 0x10) {
        if (data_ov001_020a04a0->mainBrightness == 0x10000 && data_ov001_020a04a0->subBrightness == 0x10000) {
            data_ov001_020a04a0->flags &= ~0x18;
            return func_ov001_0206a138;
        }
        fade->mainBrightness += fade->step;
        fade->subBrightness += fade->step;
        if (fade->mainBrightness > 0x10000) {
            fade->mainBrightness = 0x10000;
        }
        if (fade->subBrightness > 0x10000) {
            fade->subBrightness = 0x10000;
        }
    } else {
        if (data_ov001_020a04a0->mainBrightness == -0x10000 && data_ov001_020a04a0->subBrightness == -0x10000) {
            data_ov001_020a04a0->flags &= ~0x8;
            fade->step = 0x1800;
            return func_ov001_0206a138;
        }
        fade->mainBrightness -= fade->step;
        fade->subBrightness -= fade->step;
        if (fade->mainBrightness < -0x10000) {
            fade->mainBrightness = -0x10000;
        }
        if (fade->subBrightness < -0x10000) {
            fade->subBrightness = -0x10000;
        }
    }
    return NULL;
}
