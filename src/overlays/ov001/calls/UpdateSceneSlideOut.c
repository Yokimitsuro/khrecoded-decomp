#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 durationTicks;
    s32 from;
    s32 to;
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct Scene {
    u8 pad_000[0x47c];
    s32 slideState;
    u8 pad_480[0x15c];
    Tween slideTween;
    u8 pad_5f8[0xc];
    s32 slideOffset;
} Scene;

extern void *func_ov001_0207123c(Scene *scene);
extern void SampleTweenValue(Tween *tween, s32 *value);

void UpdateSceneSlideOut(Scene *scene)
{
    s32 value;

    func_ov001_0207123c(scene);
    SampleTweenValue(&scene->slideTween, &value);
    if (scene->slideTween.flags.finished) {
        scene->slideState = 0;
        scene->slideOffset = -1;
        return;
    }
    scene->slideOffset = value >> 12;
}
