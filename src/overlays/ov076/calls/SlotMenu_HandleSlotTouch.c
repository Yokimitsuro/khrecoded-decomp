#include "nitro/types.h"

typedef struct TouchState {
    s16 pad_00[3];
    s16 y;
    s16 pad_08;
    s16 consumed;
} TouchState;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
    s16 cursorSlot;
    u8 pad_11EEA[0x49830 - 0x11eea];
    s32 lastSlot;
} SlotMenu;

extern TouchState *func_ov039_020bca20(void);
extern int SlotMenu_GetSlotFillState(int row, int y);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

BOOL SlotMenu_HandleSlotTouch(SlotMenu *menu)
{
    TouchState *touch = func_ov039_020bca20();
    int row = menu->cursorSlot;
    int y;
    BOOL sameSlot;
    int column;
    int hit;

    y = touch->y - 0x18;
    if (menu->slotIndex == menu->lastSlot) {
        sameSlot = TRUE;
    } else {
        sameSlot = FALSE;
    }
    column = menu->column;
    touch->consumed = 0;
    if (y >= 0x40) {
        row++;
        y -= 0x40;
    }
    hit = SlotMenu_GetSlotFillState(row, y);
    if (sameSlot && column == hit && menu->slotIndex == row) {
        menu->column = hit;
        return TRUE;
    }
    if (hit >= 0) {
        menu->slotIndex = row;
        menu->column = hit;
    } else if (menu->slotIndex != row && hit > -3) {
        menu->slotIndex = row;
        hit = 0;
        menu->column = hit;
    }
    if (hit >= 0) {
        PlaySoundEffect(1, 0);
    }
    return FALSE;
}
