#include "nitro/types.h"

typedef struct ScreenFade {
    u32 flags;
    s32 progress;
    u8 pad_08[4];
    s32 brightness;
    u8 pad_10[0xC];
    s32 brightnessStep;
    u8 pad_20[0x46];
    u8 applySecondary : 1;
} ScreenFade;

typedef void *(*FadeStep)(void);

extern ScreenFade *data_ov001_020a04a0;
extern u8 sOv001_RefreshWnd_0209eb2c[];

extern void func_ov001_0206a4e4(void);
extern void NotifyBothOrOne(u32 a, void *b, int index);
extern void SetSecondaryBrightness(int brightness);
extern void *func_ov001_0206a138(void);

FadeStep ScreenFadeInStep(void)
{
    ScreenFade *fade = data_ov001_020a04a0;
    FadeStep next = NULL;

    if (fade->flags & 0x20) {
        return next;
    }
    fade->progress += (fade->flags & 0x200) ? 0x400 : 0x800;
    func_ov001_0206a4e4();
    if (fade->progress >= 0xA000) {
        fade->flags &= ~1;
        next = (FadeStep)func_ov001_0206a138;
        NotifyBothOrOne(1, sOv001_RefreshWnd_0209eb2c, 0);
        fade->brightnessStep = 0x1800;
    }
    if (fade->applySecondary) {
        SetSecondaryBrightness(fade->brightness >> 12);
    }
    fade->brightness += fade->brightnessStep;
    if (fade->brightness > 0) {
        fade->brightness = 0;
    }
    return next;
}
