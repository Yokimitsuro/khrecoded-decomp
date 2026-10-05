#include "nitro/types.h"

void ExtractTileFromSheet(u8 *tile, const u8 *sheet)
{
    int row;
    int col;
    int count;
    int offset;

    count = 0;
    offset = 0;
    for (row = 0; row < 8; row++) {
        for (col = 0; col < 8; col++) {
            tile[count] = sheet[offset + col];
            count++;
        }
        offset += 0x90;
    }
}

