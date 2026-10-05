#include "nitro/types.h"

typedef struct EntryTable {
    u8 pad_00[8];
    u32 entries[1];
} EntryTable;

typedef struct ListResource {
    u8 pad_00[8];
    EntryTable *table;
} ListResource;

typedef struct ListWidget {
    void (*onChange)(void);
    ListResource *resource;
    u8 pad_08[0x68];
    u32 values[3];
} ListWidget;

extern void RefreshListRowStates(ListWidget *list, int mode, u32 *values);

void SetListWidgetEntries(ListWidget *list, const u16 *ids)
{
    EntryTable *table = list->resource->table;
    int i;

    for (i = 0; i < 3; i++) {
        u16 id = ids[i];
        if (id == 0xffff) {
            break;
        }
        list->values[i] = table->entries[id];
    }
    for (; i < 3; i++) {
        list->values[i] = 0;
    }
    RefreshListRowStates(list, 0, list->values);
}
