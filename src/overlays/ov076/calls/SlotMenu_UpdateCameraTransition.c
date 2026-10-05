#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    u8 pad_04[0x34 - 4];
    s32 scrollY;
} ScrollList;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x11ee4 - 4];
    ScrollList list;
    u8 pad_11F1C[0x12264 - 0x11f1c];
    VecFx32 cameraPos;
    u8 pad_12270[0x49834 - 0x12270];
    s32 phase;
    Tween fadeTween;
    u8 bgPriority;
} SlotMenu;

extern void *func_ov039_020bc1dc(void);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_02052528(Tween *tween, int start, int end, int delay, int duration);
extern void func_02052570(Tween *tween);
extern void SlotMenu_ReloadSlot(SlotMenu *menu, int slot, int mode);
extern void SetBrightnessAndSyncMain(int value);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void SlotMenu_SetBg0Priority(SlotMenu *menu, int priority);
extern void func_ov076_020c8404(SlotMenu *menu);
extern void SlotMenu_SetBgScrollMode(SlotMenu *menu, int mode, int scrollY);
extern void UpdateWidgetRootAndFireAlarm(void *layout, int arg);
extern void func_ov076_020c7554(SlotMenu *menu, int mode);

void SlotMenu_UpdateCameraTransition(SlotMenu *menu)
{
    void *layout = func_ov039_020bc1dc();
    s32 value;
    VecFx32 restPos;
    VecFx32 startPos;

    startPos.x = 0x80000;
    startPos.y = 0x60000;
    startPos.z = 0x300000;
    restPos = startPos;
    SetSecondaryElementEnabled(FALSE);
    switch (menu->phase) {
    case 0:
        func_02052528(&menu->fadeTween, 0, 0, 0x10000, 0x32);
        func_02052570(&menu->fadeTween);
        menu->cameraPos = startPos;
        menu->cameraPos.x += 0x12c000;
        menu->phase = 1;
        SlotMenu_ReloadSlot(menu, menu->list.slotIndex, 0);
        SetBrightnessAndSyncMain(0x10);
        PlaySoundEffect(1, 0xc);
        break;
    case 1:
        SampleTweenValue(&menu->fadeTween, &value);
        SetBrightnessAndSyncMain(value >> 12);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 2;
            func_02052528(&menu->fadeTween, 0, 0x10000, 0, 400);
            func_02052570(&menu->fadeTween);
            menu->bgPriority = 0;
        }
        break;
    case 2:
        SampleTweenValue(&menu->fadeTween, &value);
        SetBrightnessAndSyncMain(value >> 12);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 3;
            SlotMenu_SetBg0Priority(menu, 0);
        }
        break;
    case 3:
        menu->cameraPos.x -= 0x3c000;
        if (menu->cameraPos.x < restPos.x) {
            menu->cameraPos.x = restPos.x;
            menu->phase = 4;
            func_02052528(&menu->fadeTween, 0, 0, 0, 1000);
            func_02052570(&menu->fadeTween);
        }
        break;
    case 4:
        SampleTweenValue(&menu->fadeTween, &value);
        if (menu->fadeTween.flags.finished) {
            menu->phase = 5;
        }
        break;
    case 5:
        menu->cameraPos.x -= 0x3c000;
        if (menu->cameraPos.x < restPos.x - 0x12c000) {
            SlotMenu_SetBg0Priority(menu, 1);
            func_ov076_020c8404(menu);
        }
        break;
    }
    SlotMenu_SetBgScrollMode(menu, 0, menu->list.scrollY);
    UpdateWidgetRootAndFireAlarm(layout, 0);
    func_ov076_020c7554(menu, 0);
}
