#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[0x6c38];
    u8 tileBuffer[1];
} PanelWork;

extern PanelWork *data_ov015_020812e0;
extern void BlitTileToSheet(u8 *src, u8 *dst, int mode);

void CopyTileGridToScreen(u8 *dst)
{
    int row;
    int col;
    int srcOffset;

    for (row = 0; row < 24; row++) {
        srcOffset = (row - 6) * 0x480;
        for (col = 0; col < 32; col++) {
            if (row >= 6 && row < 24 && col >= 0 && col < 18) {
                BlitTileToSheet(data_ov015_020812e0->tileBuffer + srcOffset, dst + (col * 0x40 + row * 0x800), 0);
                srcOffset += 8;
            }
        }
    }
}
