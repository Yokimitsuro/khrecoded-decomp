#include "nitro/types.h"

void BlitTileToSheet(u8 *dst, const u8 *src, BOOL transparent)
{
    int row;
    int col;
    int srcIndex = 0;
    int offset = 0;

    for (row = 0; row < 8; row++) {
        for (col = 0; col < 8; col++) {
            if (!transparent || (src[srcIndex] != 0 && src[srcIndex] != 0xf0)) {
                dst[offset + col] = src[srcIndex];
            }
            srcIndex++;
        }
        offset += 0x90;
    }
}
