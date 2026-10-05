#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee6];
    s16 slotIndex;
    s16 cursorSlot;
} SlotMenu;

extern void *func_ov039_020bc1dc(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void SetWidgetRootTouchEnabled(void *root, BOOL enabled);
extern void *G2_GetBG1ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void func_ov076_020c6328(SlotMenu *menu, int windowType, int arg2, u16 style, int messageId);

void SlotMenu_OpenSlotMessage(SlotMenu *menu, int messageId)
{
    void *root = func_ov039_020bc1dc();
    BOOL moved;
    int style;

    if (menu->slotIndex != menu->cursorSlot) {
        moved = TRUE;
    } else {
        moved = FALSE;
    }

    PlaySoundEffect(1, 1);
    SetWidgetRootTouchEnabled(root, TRUE);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x600);
    style = 3;
    if (!moved) {
        style = 0xb;
    }
    func_ov076_020c6328(menu, 2, 0, style, messageId);
}
