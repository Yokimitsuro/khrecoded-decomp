#include "nitro/types.h"

typedef u64 OSTick;

typedef struct FadeTween {
    u8 active;
    s8 busy;
    u8 pad_02[2];
    u32 startMilliseconds;
    u8 tween[0x18];
    u32 lowFlags : 2;
    u32 finished : 1;
    u32 highFlags : 29;
} FadeTween;

extern FadeTween *NNSi_FndGetCurrentRootHeap(void);
extern void SampleTweenValue(void *tween, s32 *value);
extern void SubScene9_StartFade(BOOL fadeIn);
extern OSTick OS_GetTick(void);
extern void func_ov001_02066df4(s32 value);
extern void *WaitFadeDelay(void);

void *StepFadeInTween(void)
{
    FadeTween *fade = NNSi_FndGetCurrentRootHeap();
    void *next = NULL;
    s32 value;

    SampleTweenValue(fade->tween, &value);
    if (fade->finished) {
        SubScene9_StartFade(FALSE);
        value = 0x10000;
        fade->startMilliseconds = (OS_GetTick() * 64) / 0x82ea;
        next = WaitFadeDelay;
    }
    func_ov001_02066df4(value);
    return next;
}
