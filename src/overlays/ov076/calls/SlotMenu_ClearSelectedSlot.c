#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
} SlotMenu;

extern void func_ov076_020c8a00(SlotMenu *menu, int slot, int column);
extern void func_ov076_020c6f80(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_LockTouchUntilCommit(SlotMenu *menu, BOOL unused);

void SlotMenu_ClearSelectedSlot(SlotMenu *menu)
{
    int slot = menu->slotIndex;

    func_ov076_020c8a00(menu, slot, menu->column);
    func_ov076_020c6f80(menu, slot, 0);
    SlotMenu_LockTouchUntilCommit(menu, TRUE);
}
