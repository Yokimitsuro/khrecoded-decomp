#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ListEntry {
    u16 unk_0;
    u16 column;
    u16 row;
    u16 unk_6;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[8];
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 pad_00[4];
    ListData *data;
    u8 pad_08[0x80];
    void *cellSet;
    u8 pad_8c[8];
    int baseX;
} ListView;

typedef struct ScreenPos {
    fx32 x;
    fx32 y;
} ScreenPos;

extern void func_ov027_020b91e8(void *cellSet, void *cell, ScreenPos *pos, int mode);

void PlaceCellAtListEntry_020c3700(ListView *list, int entryIndex, void *cell)
{
    ListEntry *entry = &list->data->table->entries[entryIndex];
    ScreenPos pos;

    pos.x = (list->baseX + entry->column * 8) << 12;
    pos.y = entry->row << 15;
    func_ov027_020b91e8(list->cellSet, cell, &pos, 0);
}
