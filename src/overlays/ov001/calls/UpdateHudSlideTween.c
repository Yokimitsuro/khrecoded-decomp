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
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct HudSlide {
    s32 state;
    Tween tween;
    u8 pad_20[0x10];
    s32 offset;
} HudSlide;

typedef struct HudModeFlags {
    u32 reserved : 17;
    u32 restoreOnClose : 1;
    u32 upper : 14;
} HudModeFlags;

typedef struct Hud {
    u8 pad_000[0x480];
    HudModeFlags modeFlags;
    u8 pad_484[0xcc];
    HudSlide slide;
} Hud;

extern void SampleTweenValue(Tween *tween, s32 *outValue);
extern void PlaySoundChecked(void *ptr, int arg);
extern void func_ov001_02072178(s32 value);

void UpdateHudSlideTween(Hud *hud)
{
    HudSlide *slide = &hud->slide;
    s32 value;

    if (slide->tween.flags.finished) {
        return;
    }
    SampleTweenValue(&slide->tween, &value);
    slide->offset = value >> 12;
    if (!slide->tween.flags.finished) {
        return;
    }
    if (slide->state == 1) {
        slide->state = 2;
        PlaySoundChecked(NULL, 8);
        return;
    }
    slide->state = 0;
    if (hud->modeFlags.restoreOnClose == 1) {
        func_ov001_02072178(-1);
    }
}
