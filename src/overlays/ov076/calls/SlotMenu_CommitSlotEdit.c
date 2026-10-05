#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x11ee2];
    s16 selectedSlot;
    u8 pad_11EE8[0x18];
    u8 unk_11F00;
} SlotMenu;

extern void func_ov076_020c6f80(SlotMenu *menu, int slot, int mode);
extern void func_ov076_020c8404(SlotMenu *menu);

void SlotMenu_CommitSlotEdit(SlotMenu *menu)
{
    if (menu->state == 5) {
        func_ov076_020c6f80(menu, menu->selectedSlot, 0);
        func_ov076_020c8404(menu);
    }
    menu->unk_11F00 = 0;
}
