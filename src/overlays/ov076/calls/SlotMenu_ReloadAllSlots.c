#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee4];
    s16 slotCount;
} SlotMenu;

extern SlotMenu *data_ov076_020cd400;
extern void SlotMenu_ReloadSlot(SlotMenu *menu, int slot, int mode);

void SlotMenu_ReloadAllSlots(void)
{
    int slot = 0;
    s16 slotCount = data_ov076_020cd400->slotCount;

    for (; slot < slotCount; slot++) {
        SlotMenu_ReloadSlot(data_ov076_020cd400, slot, 0);
    }
}
