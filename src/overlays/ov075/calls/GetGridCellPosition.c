#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridLayout {
    u8 pad_00[0x98];
    u8 *columnCount;
} GridLayout;

typedef struct MatrixMenu {
    u8 pad_00000[0x34];
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0x12dd0 - 0x3c];
    GridLayout *layout;
} MatrixMenu;

void GetGridCellPosition(MatrixMenu *menu, u16 *cell, fx32 *x, fx32 *y)
{
    int columns = *menu->layout->columnCount;

    *x = ((*cell % columns) * 16 + 0x80) * 0x1000 - menu->scrollX;
    *y = 0xc0000 - (((*cell / columns) * 16 + 0x58) * 0x1000 - menu->scrollY);
}