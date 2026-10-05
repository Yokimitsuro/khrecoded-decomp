#include "nitro/types.h"

typedef struct TileBlock {
    u8 pad_00[0x2c];
    u16 baseTile;
    u16 width;
    u16 height;
} TileBlock;

void WriteTileBlockToScreen(TileBlock *block, u16 (*screen)[32], int x, int y, u16 palette)
{
    u16 skip;
    u16 width;
    u16 column;
    int row;
    int col;
    u16 *dst;

    if (x < 0) {
        skip = -x;
        column = 0;
        width = block->width + x;
    } else {
        skip = 0;
        column = x;
        width = block->width;
    }
    for (row = 0; row < block->height; row++) {
        dst = &screen[y + row][column];
        for (col = 0; col < width; col++) {
            *dst++ = (block->baseTile + row * block->width + skip + col) | (palette << 12);
        }
    }
}
