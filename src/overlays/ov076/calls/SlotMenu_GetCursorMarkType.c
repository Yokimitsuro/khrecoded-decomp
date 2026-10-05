#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
    u8 pad_11EE8[0x4a078 - 0x11ee8];
    u32 markMasks[3];
} SlotMenu;

int SlotMenu_GetCursorMarkType(SlotMenu *menu)
{
    u32 bit = 1 << (menu->column + menu->slotIndex * 3);

    if (menu->markMasks[0] & bit) {
        return 0;
    }
    if (menu->markMasks[1] & bit) {
        return 1;
    }
    if (menu->markMasks[2] & bit) {
        return 2;
    }
    return -1;
}
