#include "nitro/types.h"

typedef struct SlotEntry {
    u32 inUse;
    u8 pad_04[0xC];
} SlotEntry;

typedef struct SlotTable {
    u32 count;
    SlotEntry *entries;
} SlotTable;

void SlotTable_Init(SlotTable *table, int which, u32 *data)
{
    u16 i;

    if (table == NULL || which >= 2) {
        return;
    }
    table->entries = NULL;
    for (i = 0; i < 2; i++) {
        if (which == i) {
            break;
        }
        data += *data * 4 + 1;
    }
    if (i >= 2) {
        return;
    }
    table->count = *data;
    table->entries = (SlotEntry *)(data + 1);
    for (i = 0; i < table->count; i++) {
        table->entries[i].inUse = 0;
    }
}
