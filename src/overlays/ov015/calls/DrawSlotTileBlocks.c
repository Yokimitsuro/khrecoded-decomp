#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPoint;

typedef struct {
    u8 pad_0000[0x65f8];
    u8 tileData[25 * 0x40];
    u8 mask[1];
} TileSheet;

extern TileSheet *data_ov015_020812e0;
extern PanelPoint *gWirelessModeDataTables[];
extern void FillTileInSheet(u8 *dst, const u8 *src, int fill);
extern void BlitTileToSheet(u8 *dst, const u8 *src, BOOL transparent);

void DrawSlotTileBlocks(u8 *dst, int count, int only, int fill, BOOL blit)
{
    int row;
    int i;
    PanelPoint *points = gWirelessModeDataTables[count];
    int col;
    int base;
    int offset;

    for (i = 0; i < count; i++) {
        if (only < 0 || only == i) {
            base = (points[i].y - 0x30) * 0x90 + points[i].x;
            for (row = 0; row < 5; row++) {
                int lineOffset = row * 0x480;

                for (col = 0; col < 5; col++) {
                    offset = base + lineOffset;
                    FillTileInSheet(dst + offset, data_ov015_020812e0->mask + offset, fill);
                    if (blit) {
                        BlitTileToSheet(dst + offset, data_ov015_020812e0->tileData + (col * 0x40 + row * 0x140), TRUE);
                    }
                    lineOffset += 8;
                }
            }
        }
    }
}
