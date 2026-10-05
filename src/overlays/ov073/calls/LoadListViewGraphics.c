#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    u8 data[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct RowEntry {
    u16 value;
    u16 x;
    u16 y;
    u16 unk_6;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[6];
    u16 count;
    RowEntry entries[1];
} RowTable;

typedef struct ListNode {
    u8 pad_00[6];
    u16 parentRow;
} ListNode;

typedef struct NodeTable {
    u8 pad_00[6];
    u16 count;
    ListNode *nodes[1];
} NodeTable;

typedef struct ListData {
    u8 pad_00[4];
    RowTable *rows;
    NodeTable *nodes;
} ListData;

typedef struct ListOverlayCell {
    int cellIndex;
    int slotId;
    fx32 x;
    fx32 y;
} ListOverlayCell;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    u8 pad_08[0x70 - 0x08];
    ListNode *path[3];
    u8 pad_7c[4];
    u8 *rowStates;
    u8 pad_84[4];
    void *cellSet;
    u8 pad_8c[0x94 - 0x8c];
    int scrollX;
    u8 pad_98[0xac - 0x98];
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
} ListView;

extern int *GetSelectionPackedValueBlock(void);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GXS_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void RefreshListRowStates(ListView *list, int start, ListNode **path);
extern int PXI_Init_0204f0c8(void *cellSet, int sequence, int arg);
extern void IndexedRecord_SetPair(void *cellSet, int cellIndex, ScreenPos *pos);

void LoadListViewGraphics(ListView *list, void *archive, void *screenBuffer)
{
    int *selection = GetSelectionPackedValueBlock();
    BgGraphicsData bg;
    RowTable *rows;
    NodeTable *nodes;
    void *cellSet;
    ListOverlayCell *cell;
    RowEntry *entry;
    ListOverlayCell *cells;
    int sequence;
    ScreenPos pos;
    int i;
    int j;

    GetBgDataFromArchive(&bg, archive, 0, 0, -1);
    GXS_LoadBG2Char(bg.character->data, 0, bg.character->size);
    MIi_CpuCopy16(bg.screen->data, screenBuffer, bg.screen->size);
    if (*selection >= 0) {
        RefreshListRowStates(list, 0, list->path);
    } else {
        RefreshListRowStates(list, 0, NULL);
    }
    nodes = list->data->nodes;
    rows = list->data->rows;
    cellSet = list->cellSet;
    for (i = 0; i < rows->count; i++) {
        entry = &rows->entries[i];
        for (j = 0; j < nodes->count; j++) {
            if (i == nodes->nodes[j]->parentRow) {
                break;
            }
        }
        if (j == nodes->count) {
            sequence = list->rowStates[i] == 0 ? list->normalSequence : list->highlightSequence;
            cells = list->overlayCells;
            cell = &cells[list->overlayCellCount];
            cell->cellIndex = PXI_Init_0204f0c8(cellSet, sequence, 0);
            cell->slotId = entry->value;
            cell->x = entry->x << 15;
            cell->y = entry->y << 15;
            list->overlayCellCount++;
        }
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        cell = &list->overlayCells[i];
        pos.x = cell->x + (list->scrollX << 12);
        pos.y = cell->y;
        IndexedRecord_SetPair(list->cellSet, cell->cellIndex, &pos);
    }
    if (list->onChange != NULL) {
        list->onChange();
    }
}
