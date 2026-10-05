#include "nitro/types.h"

typedef struct FadeTween {
    u8 active;
    s8 busy;
    u8 pad_02[6];
    u8 tween[0x18];
    u32 lowFlags : 2;
    u32 finished : 1;
    u32 highFlags : 29;
} FadeTween;

extern FadeTween *NNSi_FndGetCurrentRootHeap(void);
extern void SampleTweenValue(void *tween, s32 *value);
extern void func_ov001_02066df4(s32 value);
extern void *func_ov001_02066cb4(void);

void *StepFadeTween(void)
{
    FadeTween *fade = NNSi_FndGetCurrentRootHeap();
    void *next = NULL;
    s32 value;

    SampleTweenValue(fade->tween, &value);
    if (fade->finished && fade->busy == 0) {
        fade->active = 0;
        next = func_ov001_02066cb4;
    }
    func_ov001_02066df4(value);
    return next;
}
