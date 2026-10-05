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
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x49838 - 4];
    Tween fadeTween;
    u8 bgPriority;
    u8 altView;
} SlotMenu;

extern void SetSecondaryElementEnabled(BOOL enabled);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_02052528(Tween *tween, int start, int end, int delay, int duration);
extern void func_02052570(Tween *tween);
extern void SlotMenu_RefreshView(SlotMenu *menu);

void SlotMenu_ToggleViewAfterTween(SlotMenu *menu)
{
    s32 value;

    SetSecondaryElementEnabled(FALSE);
    if (menu->state != 5) {
        SampleTweenValue(&menu->fadeTween, &value);
        if (menu->fadeTween.flags.finished) {
            func_02052528(&menu->fadeTween, 0, 0, 0, 500);
            func_02052570(&menu->fadeTween);
            menu->altView = !menu->altView;
        }
    }
    SlotMenu_RefreshView(menu);
}
