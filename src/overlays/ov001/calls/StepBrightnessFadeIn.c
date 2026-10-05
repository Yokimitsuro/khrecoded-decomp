#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void *(*FadeStepFn)(void);

typedef struct FadeState {
    u32 flags;
    u8 pad_04[4];
    fx32 mainLevel;
    fx32 subLevel;
    u8 pad_10[0xc];
    fx32 step;
    u8 pad_20[0x46];
    u8 fadeSub : 1;
    u8 pad_66_bits : 7;
} FadeState;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 flags;
} FieldState;

extern FadeState *data_ov001_020a04a0;
extern FieldState *data_ov001_020a0480;
extern void SetBrightnessAndSyncMain(int level);
extern void SetSecondaryBrightness(int level);
extern void *func_ov001_0206a138(void);

FadeStepFn StepBrightnessFadeIn(void)
{
    FadeState *fade = data_ov001_020a04a0;

    if (fade->flags & 0x20) {
        return NULL;
    }
    SetBrightnessAndSyncMain(fade->mainLevel >> 12);
    if (fade->fadeSub) {
        SetSecondaryBrightness(fade->subLevel >> 12);
    }
    if (fade->mainLevel == 0 && fade->subLevel == 0) {
        fade->flags &= ~0x14;
        fade->step = 0x1800;
        if (fade->fadeSub) {
            data_ov001_020a0480->flags &= ~0x40000;
            fade->fadeSub = 0;
        }
        return func_ov001_0206a138;
    }
    if (fade->flags & 0x10) {
        fade->mainLevel -= fade->step;
        fade->subLevel -= fade->step;
        if (fade->mainLevel < 0) {
            fade->mainLevel = 0;
        }
        if (fade->subLevel < 0) {
            fade->subLevel = 0;
        }
    } else {
        fade->mainLevel += fade->step;
        fade->subLevel += fade->step;
        if (fade->mainLevel > 0) {
            fade->mainLevel = 0;
        }
        if (fade->subLevel > 0) {
            fade->subLevel = 0;
        }
    }
    return NULL;
}
