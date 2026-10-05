#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

typedef struct ListOverlayCell {
    int cellIndex;
    int unk_4;
    fx32 x;
    fx32 y;
} ListOverlayCell;

typedef struct ListView {
    u8 pad_00[0x88];
    void *cellSet;
    void *highlightCell;
    u8 pad_90[4];
    int baseX;
    u8 pad_98[0x10];
    int selectedIndex;
    int overlayCellCount;
    ListOverlayCell overlayCells[1];
} ListView;

extern void PlaceCellAtListEntry_020c3700(ListView *list, int entryIndex, void *cell);
extern void IndexedRecord_SetPair(void *cellSet, int cellIndex, ScreenPos *pos);

void SelectListEntry(ListView *list, int entryIndex)
{
    int i;
    ScreenPos pos;

    PlaceCellAtListEntry_020c3700(list, entryIndex, list->highlightCell);
    list->selectedIndex = entryIndex;
    for (i = 0; i < list->overlayCellCount; i++) {
        ListOverlayCell *cell = &list->overlayCells[i];
        pos.x = cell->x + (list->baseX << 12);
        pos.y = cell->y;
        IndexedRecord_SetPair(list->cellSet, cell->cellIndex, &pos);
    }
}
