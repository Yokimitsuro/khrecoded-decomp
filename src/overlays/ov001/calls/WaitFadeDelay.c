#include "nitro/types.h"

typedef struct FadeDelay {
    u32 unk_00;
    int startMilliseconds;
} FadeDelay;

extern FadeDelay *NNSi_FndGetCurrentRootHeap(void);
extern u64 OS_GetTick(void);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern void SetMainBrightnessFromFx(s32 value);
extern void *StepFadeTween(void);

void *WaitFadeDelay(void)
{
    FadeDelay *fade = NNSi_FndGetCurrentRootHeap();
    void *next = NULL;

    if (fade->startMilliseconds + 100 < _ll_udiv(OS_GetTick() * 64, 0x82ea)) {
        next = StepFadeTween;
    }
    SetMainBrightnessFromFx(0x10000);
    return next;
}
