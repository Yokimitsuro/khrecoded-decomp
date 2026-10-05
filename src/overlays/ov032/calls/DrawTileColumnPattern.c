#include "nitro/types.h"

extern const u8 data_ov032_020bff78[][5];
extern void SetTilePixel4bpp(u8 *tiles, int x, u16 y, u8 color);

void DrawTileColumnPattern(u8 *tiles, int x, int pattern)
{
    int i;
    for (i = 0; i < 5; i++) {
        SetTilePixel4bpp(tiles, x, i + 2, data_ov032_020bff78[pattern][i]);
    }
}
