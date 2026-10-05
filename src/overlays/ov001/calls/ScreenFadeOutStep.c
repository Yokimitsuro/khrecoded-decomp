#include "nitro/types.h"

typedef struct ScreenFade {
    u32 flags;
    s32 progress;
    u8 pad_08[4];
    s32 brightness;
    u8 pad_10[0xC];
    s32 brightnessStep;
} ScreenFade;

typedef void *(*FadeStep)(void);

extern ScreenFade *data_ov001_020a04a0;

extern void func_ov001_0206a4e4(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetSecondaryBrightness(int brightness);
extern void *func_ov001_0206a138(void);

FadeStep ScreenFadeOutStep(void)
{
    ScreenFade *fade = data_ov001_020a04a0;
    FadeStep next = NULL;

    if (fade->flags & 0x20) {
        return next;
    }
    fade->progress -= (fade->flags & 0x200) ? 0x400 : 0x800;
    func_ov001_0206a4e4();
    if (fade->progress <= 0x100) {
        fade->flags &= ~2;
        next = (FadeStep)func_ov001_0206a138;
        if (!(fade->flags & 0x100)) {
            SetBrightnessAndSyncMain(-16);
        }
        fade->brightnessStep = 0x1800;
    }
    if (!(fade->flags & 0x100)) {
        SetSecondaryBrightness(fade->brightness >> 12);
    }
    fade->brightness -= fade->brightnessStep;
    if (fade->brightness < -0x10000) {
        fade->brightness = -0x10000;
    }
    return next;
}
