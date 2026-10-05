#include "nitro/types.h"

void SetTilePixel4bpp(u8 *tiles, int x, int y, u8 color)
{
    u8 *pixel = &tiles[((u32)x >> 3) * 32 + y * 4 + (x % 8) / 2];
    if (x & 1) {
        *pixel = (*pixel & 0xf) | (color << 4);
    } else {
        *pixel = (*pixel & 0xf0) | color;
    }
}
