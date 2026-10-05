#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    s8 id;
    u8 pad_03[0x151];
} SlotEntry;

typedef struct {
    u8 pad_00[8];
    SlotEntry *entries;
    u8 pad_0c[9];
    u8 count;
} SlotTable;

void SlotTable_ResetIds(SlotTable *table)
{
    int i;
    int count = table->count;

    for (i = 0; i < count; i++) {
        table->entries[i].id = -1;
    }
}
