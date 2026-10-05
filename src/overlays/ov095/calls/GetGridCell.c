#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    u32 *cells;
    int width;
} CellGridHeader;

u32 GetGridCell(int column, int row, u8 *owner)
{
    u8 *grid = owner + 0xa4;
    CellGridHeader *header = (CellGridHeader *)(grid + 0x11000);
    return header->cells[row * header->width + column];
}
