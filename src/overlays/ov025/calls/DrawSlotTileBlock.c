#include "nitro/types.h"

typedef struct ListOverlayCell {
    int cellIndex;
    int group;
    int x;
    int y;
} ListOverlayCell;

typedef struct ListView {
    u8 pad_00[0x88];
    void *cellSet;
    u8 pad_8c[0x20];
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
} ListView;

extern u16 *GetTileMapEntry(int x, int y, int layer);
extern void SetSlotAnimSequence(void *owner, int slot, int sequence);

void DrawSlotTileBlock(ListView *list, int group, int x, int y, int layer, u16 baseTile, int palette)
{
    u16 *screen = GetTileMapEntry(x, y, layer);
    int col;
    u16 *dst;
    int row;
    int i;

    for (row = 0; row < 2; row++) {
        dst = screen + row * 32;
        for (col = 0; col < 12; col++) {
            *dst = (baseTile + row * 12 + col) | (palette << 12);
            dst++;
        }
    }
    dst = screen + 64;
    for (col = 0; col < 12; col++) {
        *dst = (col + 0x19) | (palette << 12);
        dst++;
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        ListOverlayCell *cell = &list->overlayCells[i];
        if (cell->group == group) {
            SetSlotAnimSequence(list->cellSet, cell->cellIndex,
                                         (palette == 12 || palette == 11) ? list->highlightSequence
                                                                          : list->normalSequence);
        }
    }
}
