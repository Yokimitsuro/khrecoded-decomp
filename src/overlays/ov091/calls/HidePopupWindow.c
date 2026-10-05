#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int frameSlot;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void SetSubBg2Visible(void *scene, BOOL visible);
extern void SetPopupSlotVisible(int slotIndex, BOOL visible);
extern void ClosePopupText(void *window);
extern void SetPopupState(void *machine, s32 state);

void HidePopupWindow(void *popup)
{
    SetSubBg2Visible(popup, FALSE);
    SetPopupSlotVisible(data_ov091_020c375c->frameSlot, FALSE);
    ClosePopupText(popup);
    SetPopupState(popup, 0);
}
