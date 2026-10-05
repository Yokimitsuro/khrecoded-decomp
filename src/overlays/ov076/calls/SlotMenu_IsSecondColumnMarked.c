#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00[0x14];
    s32 column;
} SlotMenu;

extern int SlotMenu_GetCursorMarkType(SlotMenu *menu);

BOOL SlotMenu_IsSecondColumnMarked(SlotMenu *menu)
{
    int markType = SlotMenu_GetCursorMarkType(menu);

    if ((markType == 0 || markType == 1) && menu->column == 1) {
        return TRUE;
    }
    return FALSE;
}
