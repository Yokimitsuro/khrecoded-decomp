#include "nitro/types.h"

typedef struct {
    u16 rows;
    u16 cols;
    u8 pad_04[0x14 - 0x4];
    u8 *tiles;
} TileImage;

typedef struct {
    u8 pad_00[4];
    TileImage *image;
} TileSource;

typedef struct {
    u8 pad_00[0x904];
    u8 charData[0x10000];
    u8 pad_10904[0x10940 - 0x10904];
} ScrollScreen;

typedef struct {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);

void CopyScrollTextTiles(TileSource *source, int screenIndex, int column, int row)
{
    int i;
    int j;
    int columnBase;
    int rowIndex;
    int rowOffset;

    columnBase = column & 0x1f;
    for (i = 0; i < 27; i++) {
        rowIndex = row - 1 + i;
        rowOffset = (rowIndex & 0x1f) * 0x800;
        if (rowIndex >= 0 && rowIndex < source->image->rows) {
            for (j = 0; j < 10; j++) {
                int col = column + j;
                TileImage *image = source->image;
                u8 *charData = data_ov004_020645a0.work->screens[screenIndex].charData;
                int cols = image->cols;
                int tileIndex = rowIndex * cols + col;
                u8 *dest = charData + (((j + columnBase) & 0x1f) * 0x40 + rowOffset);

                if (col < 0 || col >= cols) {
                    MIi_CpuClearFast(0, dest, 0x40);
                } else {
                    MIi_CpuCopyFast(image->tiles + tileIndex * 0x40, dest, 0x40);
                }
            }
        }
    }
    NNS_GfdRegisterNewVramTransferTask(screenIndex == 0 ? 6 : 0x16, 0, data_ov004_020645a0.work->screens[screenIndex].charData, 0x10000);
}
