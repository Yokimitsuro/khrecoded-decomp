#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x49818];
    u16 slotPoints[8];
} SlotMenu;

BOOL SlotMenu_IsPointTotalOverLimit(SlotMenu *menu)
{
    int total = 0;
    int slot;

    for (slot = 0; slot < 8; slot++) {
        total += menu->slotPoints[slot];
    }
    return total > 100;
}
