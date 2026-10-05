#include "nitro/types.h"

typedef struct SlotEntry {
    u32 inUse;
    u8 pad_04[0xC];
} SlotEntry;

typedef struct SlotTable {
    u32 count;
    SlotEntry *entries;
} SlotTable;

SlotEntry *SlotTable_GetEntry(SlotTable *table, int index)
{
    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if ((u32)index >= table->count) {
        return NULL;
    }
    return &table->entries[index];
}
