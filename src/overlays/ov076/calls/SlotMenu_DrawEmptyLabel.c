#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee8];
    s16 cursorSlot;
    u8 pad_11EEA[0x1c6f8 - 0x11eea];
    u8 labelTemplate[0x780];
    u8 thirdLabelTemplate[0x780];
} SlotMenu;

extern void SlotMenu_UploadLabel(SlotMenu *menu, int slot, int part, u8 *buffer);

void SlotMenu_DrawEmptyLabel(SlotMenu *menu, int slot, int part)
{
    int offset = slot - menu->cursorSlot;
    u8 *buffer;

    if (offset < -1 || offset > 2) {
        return;
    }
    if (part == 2) {
        buffer = menu->thirdLabelTemplate;
    } else {
        buffer = menu->labelTemplate;
    }
    SlotMenu_UploadLabel(menu, slot, part, buffer);
}
