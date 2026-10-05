#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00[0x14];
    s32 column;
} SlotMenu;

extern int SlotMenu_GetCursorMarkType(SlotMenu *menu);

BOOL SlotMenu_IsThirdColumnMarked(SlotMenu *menu)
{
    int markType = SlotMenu_GetCursorMarkType(menu);

    if ((markType == 0 || markType == 2) && menu->column == 2) {
        return TRUE;
    }
    return FALSE;
}
