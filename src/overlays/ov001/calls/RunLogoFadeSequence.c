#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s32 startTick[2];
    TweenFlags flags;
} Tween;

typedef struct {
    u8 pad_00[0xa4];
    s32 scale;
} FadeNode;

typedef struct {
    u32 pad_000;
    s32 active;
    u8 pad_008[0x104];
    u32 state;
    u8 pad_110[0x8c];
    Tween tween;
    FadeNode node;
} FadeSequence;

extern void StartTimerFromPackedPair(Tween *tween, u32 packed, int duration);
extern void PlaySoundChecked(void *ptr, int arg);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_ov001_0207c988(void);
extern void func_01ffb12c(FadeNode *node);

void RunLogoFadeSequence(FadeSequence *sequence)
{
    Tween *tween = &sequence->tween;
    FadeNode *node = &sequence->node;

    switch (sequence->state) {
    case 0:
        StartTimerFromPackedPair(tween, 0x20000, 500);
        PlaySoundChecked(0, 0x38);
        sequence->state++;
    case 1:
        SampleTweenValue(tween, &node->scale);
        if (!tween->flags.finished) {
            break;
        }
        StartTimerFromPackedPair(tween, 0, 1000);
        sequence->state++;
    case 2:
        SampleTweenValue(tween, &node->scale);
        if (!tween->flags.finished) {
            break;
        }
        StartTimerFromPackedPair(tween, 0xfffe, 500);
        sequence->state++;
    case 3:
        SampleTweenValue(tween, &node->scale);
        if (!tween->flags.finished) {
            break;
        }
        sequence->state++;
        sequence->active = 0;
    }
    if (sequence->state < 4) {
        func_ov001_0207c988();
        func_01ffb12c(node);
    }
}

