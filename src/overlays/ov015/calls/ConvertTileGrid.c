#include "nitro/types.h"

extern void ExtractTileFromSheet(u8 *dst, u8 *src);
extern int NNS_GfdRegisterNewVramTransferTask(u32 command, u32 offset, void *data, u32 size);

void ConvertTileGrid(u8 *dst, u8 *src, u32 command, int tileOffset)
{
    int row;
    int col;
    int srcOffset;

    for (row = 0; row < 18; row++) {
        srcOffset = row * 0x480;
        for (col = 0; col < 18; col++) {
            ExtractTileFromSheet(dst + (row * 0x480 + col * 0x40), src + srcOffset);
            srcOffset += 8;
        }
    }
    NNS_GfdRegisterNewVramTransferTask(command, tileOffset << 6, dst, 0x5100);
}
