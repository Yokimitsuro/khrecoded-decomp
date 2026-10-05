#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    s32 phase;
    u8 pad_0c[0x23ac8 - 0xc];
    s32 exitMode;
    u8 pad_23acc[0x30344 - 0x23acc];
    FrameTimer fadeTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern char sOv004_SfV_02064578[];
extern void (*gScrollTextHandlers[])(void);

extern u16 FrameTimer_Interpolate(FrameTimer *timer, u16 value);
extern BOOL FrameTimer_IsExpired(FrameTimer *timer);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern BOOL IsSoundStreamActive(int handleIndex);
extern void NotifyBothOrOne(u32 a, char *name, int index);

void UpdateScrollTextFadeOut(void)
{
    int brightness = -(s16)FrameTimer_Interpolate(&data_ov004_020645a0.work->fadeTimer, 16);

    SetBrightnessAndSyncMain(brightness);
    SetSecondaryBrightness(brightness);
    if (FrameTimer_IsExpired(&data_ov004_020645a0.work->fadeTimer) &&
        !IsSoundStreamActive(0)) {
        if (data_ov004_020645a0.work->phase == 1) {
            NotifyBothOrOne(1, sOv004_SfV_02064578, 0);
        }
        data_ov004_020645a0.work->mode = data_ov004_020645a0.work->exitMode == 1 ? 3 : 4;
    }
    gScrollTextHandlers[data_ov004_020645a0.work->phase]();
}
