#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x13eb0];
    s16 cursorX;
    s16 cursorY;
    u8 pad_13eb4[0x13ec4 - 0x13eb4];
    u8 selectedColumn;
} MatrixMenu;

void MoveCursorToSelectedColumn(MatrixMenu *menu)
{
    menu->cursorX = menu->selectedColumn * 24 + 16;
    menu->cursorY = 20;
}
