#include "nitro/types.h"

void FillTileInSheet(u8 *dst, const u8 *src, int fill)
{
    int row;
    int col;
    int offset = 0;

    for (row = 0; row < 8; row++) {
        for (col = 0; col < 8; col++) {
            if (fill < 0) {
                dst[offset + col] = src[offset + col];
            } else {
                dst[offset + col] = fill;
            }
        }
        offset += 0x90;
    }
}
