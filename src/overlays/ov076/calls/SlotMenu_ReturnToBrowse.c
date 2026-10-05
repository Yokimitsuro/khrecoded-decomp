#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x10];
    s32 column;
    u8 pad_00018[0x1c6dc];
    u32 stateTimer;
    u8 pad_1C6F8[0x2d15d];
    u8 highlightVisible;
} SlotMenu;

void SlotMenu_ReturnToBrowse(SlotMenu *menu)
{
    menu->state = 1;
    menu->stateTimer = 0;
    menu->highlightVisible = FALSE;
    menu->column = 0;
}
