#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
} SlotMenu;

extern void SlotMenu_UnequipSlotEntry(SlotMenu *menu, int slot, int column);
extern void SlotMenu_ReloadSlot(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_LockTouchUntilCommit(SlotMenu *menu, BOOL unused);

void SlotMenu_ClearSelectedSlot(SlotMenu *menu)
{
    int slot = menu->slotIndex;

    SlotMenu_UnequipSlotEntry(menu, slot, menu->column);
    SlotMenu_ReloadSlot(menu, slot, 0);
    SlotMenu_LockTouchUntilCommit(menu, TRUE);
}
