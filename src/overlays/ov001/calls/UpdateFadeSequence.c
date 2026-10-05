#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration_ticks;
    s32 from;
    s32 to;
    long long startTick;
    TweenFlags flags;
} Tween;

typedef struct FadeSequence {
    u32 unk0;
    int active;
    u8 pad8[0x104];
    int step;
    u8 pad110[0x4d4];
    Tween tween;
    u8 node[4];
} FadeSequence;

extern void StartTimerFromPackedPair(void *record, u32 packed, int extra);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_ov001_0207c988(void);
extern void func_01ffb12c(void *node);

void UpdateFadeSequence(FadeSequence *sequence) {
    Tween *tween = &sequence->tween;

    switch (sequence->step) {
    case 0:
        StartTimerFromPackedPair(tween, 0, 0x4e2);
        sequence->step++;
    case 1:
        SampleTweenValue(tween, NULL);
        if (tween->flags.finished) {
            sequence->step++;
            sequence->active = 0;
        }
        break;
    }
    if (sequence->step == 1) {
        func_ov001_0207c988();
        func_01ffb12c(sequence->node);
    }
}
