#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[4];
    BOOL started;
    u8 pad_0000C[0x24 - 0xc];
    u8 navigation[0x718 - 0x24];
    u8 animation[0x7fc0 - 0x718];
    u8 panel[0x11ee0 - 0x7fc0];
    s32 panelMode;
    u8 pad_11EE4[0x49856 - 0x11ee4];
    u8 animationActive;
} SlotMenu;

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern BOOL AdvanceAnimationTracks(void *animation, int step);
extern void func_01ffb12c(void *animation);
extern void func_ov073_020c2cc4(int page, int index);
extern void RuntimeState_SetCondition(int value);
extern u32 func_ov039_020bc0f4(void);
extern void *func_ov039_020bc1dc(void);
extern void MessageWindow_Update(void *panel, u32 input);
extern BOOL func_ov076_020c8b48(SlotMenu *menu);
extern int func_ov076_020ccbd0(void *navigation, int mode, BOOL locked);
extern void SlotMenu_ShowPointLimitWarning(SlotMenu *menu);
extern void func_ov076_020c4db4(SlotMenu *menu);
extern void SlotMenu_UpdateIdle(SlotMenu *menu);
extern void func_ov076_020c548c(SlotMenu *menu);
extern void func_ov076_020c5c2c(SlotMenu *menu);
extern void SlotMenu_UpdateMessageWait(SlotMenu *menu);
extern void func_ov076_020c5ca0(SlotMenu *menu);
extern void SlotMenu_ToggleViewAfterTween(SlotMenu *menu);
extern void func_ov076_020c5d30(SlotMenu *menu);
extern void func_ov076_020c5d38(SlotMenu *menu);
extern void SlotMenu_UpdateCameraTransition(SlotMenu *menu);
extern BOOL SlotMenu_HasThreeFilledSlotsAndFlags(SlotMenu *menu);
extern BOOL SlotMenu_OpenEmptySlot(SlotMenu *menu);
extern void SetNavigationElementsVisible(void *container, BOOL visible);
extern void func_ov076_020c8198(SlotMenu *menu, int mode);

void SlotMenu_Update(SlotMenu *menu)
{
    BOOL withinLimit;
    int touched;

    if (menu->panelMode != 1) {
        MessageWindow_Update(menu->panel, func_ov039_020bc0f4());
    }
    withinLimit = func_ov076_020c8b48(menu);
    touched = func_ov076_020ccbd0(menu->navigation, 2, withinLimit);
    if (touched >= 0 && touched != 1 && !withinLimit) {
        SlotMenu_ShowPointLimitWarning(menu);
    }
    switch (menu->state) {
    case 0:
        func_ov076_020c4db4(menu);
        break;
    case 2:
        SlotMenu_UpdateIdle(menu);
        break;
    case 1:
        func_ov076_020c548c(menu);
        break;
    case 3:
        func_ov076_020c5c2c(menu);
        break;
    case 4:
        SlotMenu_UpdateMessageWait(menu);
        break;
    case 6:
        func_ov076_020c5ca0(menu);
        break;
    case 5:
    case 7:
        SlotMenu_ToggleViewAfterTween(menu);
        break;
    case 8:
        func_ov076_020c5d30(menu);
        break;
    case 9:
        func_ov076_020c5d38(menu);
        break;
    case 10:
        SlotMenu_UpdateCameraTransition(menu);
        break;
    }
    if (menu->animationActive != 0 && !AdvanceAnimationTracks(menu->animation, 0x1000)) {
        func_01ffb12c(menu->animation);
    } else {
        menu->animationActive = 0;
    }
    if (!menu->started) {
        func_ov073_020c2cc4(1, -1);
        RuntimeState_SetCondition(1);
        menu->started = TRUE;
        if (!IsGlobalPackedBitSet(0xf74) ||
            (!IsGlobalPackedBitSet(0xfbe) && SlotMenu_HasThreeFilledSlotsAndFlags(menu)) ||
            (!IsGlobalPackedBitSet(0xf75) && SlotMenu_OpenEmptySlot(menu))) {
            SetNavigationElementsVisible(func_ov039_020bc1dc(), FALSE);
            func_ov076_020c8198(menu, 0);
        }
    }
}
