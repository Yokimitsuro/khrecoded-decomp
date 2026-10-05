#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 slotLimit;
} SaveData;

typedef struct SlotMenu {
    u8 pad_00000[0x11ee8];
    s16 cursorSlot;
} SlotMenu;

extern SaveData *data_0205fe0c;
extern void func_ov076_020c6f80(SlotMenu *menu, int slot, int mode);

void SlotMenu_ReloadVisibleSlots(SlotMenu *menu)
{
    int limit = data_0205fe0c->slotLimit + 2;
    int last = menu->cursorSlot + 2;
    int slot;

    if (last > limit) {
        last = limit;
    }
    slot = menu->cursorSlot - 1;
    if (slot < 0) {
        slot = 0;
    }
    for (; slot <= last; slot++) {
        func_ov076_020c6f80(menu, slot, 0);
    }
}
