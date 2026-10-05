#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x7fc0 - 4];
    u8 messageWindow[0x1c6f4 - 0x7fc0];
    u32 stateTimer;
} SlotMenu;

extern SlotMenu *data_ov076_020cd400;

extern void SlotMenu_ShowSlotHint(SlotMenu *menu);
extern void *func_ov039_020bc1dc(void);
extern void SetNavigationElementsVisible(void *container, BOOL visible);
extern void SlotMenu_LockTouchUntilCommit(SlotMenu *menu, BOOL unused);
extern BOOL MessageWindow_IsFinished(void *window);
extern void SlotMenu_ReturnToBrowse(SlotMenu *menu);
extern void SlotMenu_SetReturnCallback(SlotMenu *menu);
extern void SlotMenu_ClearSelectedSlot(SlotMenu *menu);

void SlotMenu_OnMessageConfirm(SlotMenu *menu, BOOL accepted)
{
    switch (menu->state) {
    case 3:
        if (accepted) {
            menu->state = 4;
            return;
        }
        menu->state = 1;
        menu->stateTimer = 0;
        SlotMenu_ShowSlotHint(data_ov076_020cd400);
        SetNavigationElementsVisible(func_ov039_020bc1dc(), TRUE);
        SlotMenu_LockTouchUntilCommit(menu, FALSE);
        return;
    case 6:
    case 7:
        if (MessageWindow_IsFinished(menu->messageWindow)) {
            SlotMenu_ReturnToBrowse(menu);
            return;
        }
        break;
    case 9:
        SlotMenu_SetReturnCallback(menu);
        menu->state = 1;
        menu->stateTimer = 0;
        return;
    case 8:
        if (accepted) {
            SlotMenu_ClearSelectedSlot(menu);
        } else {
            SlotMenu_LockTouchUntilCommit(menu, TRUE);
        }
        menu->state = 1;
        menu->stateTimer = 0;
        SlotMenu_ShowSlotHint(data_ov076_020cd400);
        SetNavigationElementsVisible(func_ov039_020bc1dc(), TRUE);
        break;
    }
}
