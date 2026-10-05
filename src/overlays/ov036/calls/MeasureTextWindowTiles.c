#include "nitro/types.h"

typedef struct TextSize {
    s32 width;
    s32 height;
} TextSize;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern u8 *gTextWindowResourceTable;
extern void NNSi_G2dFontGetTextRect(TextSize *outSize, void *font, int hSpace, int vSpace, const u16 *text);

void MeasureTextWindowTiles(TextSize *outTiles, int compact, const u16 *text, int padX, int padY)
{
    u8 *work = gTextWindowResourceTable;
    int maxWidth = 0x1e;
    int maxHeight = 0x16;
    TextSize tiles;
    TextSize measured;

    if (compact == 1) {
        maxWidth = 0x10;
        maxHeight = 9;
    }
    NNSi_G2dFontGetTextRect(&measured, work + 0x644c, 0, 2, text);
    tiles = measured;
    if (tiles.width < 0x10) {
        tiles.width = 0x10;
    }
    tiles.width += padX;
    tiles.height += padY;
    tiles.width = MIN((tiles.width + 7) / 8, 0x1c);
    tiles.height = (tiles.height + 7) / 8;
    if (tiles.width > maxWidth) {
        tiles.width = maxWidth;
    }
    if (tiles.height > maxHeight) {
        tiles.height = maxHeight;
    }
    *outTiles = tiles;
}
