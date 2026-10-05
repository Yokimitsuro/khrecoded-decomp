#include "nitro/types.h"

typedef struct ListOverlayCell {
    int cellIndex;
    int slotId;
    u8 pad_08[8];
} ListOverlayCell;

typedef struct ListView {
    u8 pad_00[0x88];
    void *cellSet;
    u8 pad_8c[0xac - 0x8c];
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
} ListView;

extern u16 *GetScreenTilePtr(int x, int y, int screen);
extern void SetSlotAnimSequence(void *cellSet, int slot, int sequence);

void DrawListSlotTiles(ListView *list, int slotId, int x, int y, int screen, u16 tileBase, int palette)
{
    u16 *map = GetScreenTilePtr(x, y, screen);
    u16 *dst;
    int row;
    int col;
    int i;

    for (row = 0; row < 2; row++) {
        dst = map + row * 0x20;
        for (col = 0; col < 12; col++) {
            *dst++ = (tileBase + row * 12 + col) | (palette << 12);
        }
    }
    dst = map + 0x40;
    for (col = 0; col < 12; col++) {
        *dst++ = (col + 0x19) | (palette << 12);
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        ListOverlayCell *cell = &list->overlayCells[i];
        if (cell->slotId == slotId) {
            SetSlotAnimSequence(list->cellSet, cell->cellIndex,
                                         (palette == 12 || palette == 11) ? list->highlightSequence : list->normalSequence);
        }
    }
}
