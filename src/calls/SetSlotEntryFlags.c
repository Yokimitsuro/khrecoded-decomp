#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x78];
    u32 unused : 4;
    u32 flagA : 1;
    u32 flagB : 1;
    u32 rest : 26;
    u8 pad_7c[0x8c - 0x7c];
} SlotEntry;

typedef struct SlotTable {
    u32 header;
    SlotEntry entries[1];
} SlotTable;

void SetSlotEntryFlags(SlotTable *table, int index, u32 flags)
{
    SlotEntry *entry = &table->entries[index];

    if (index < 0) {
        return;
    }
    entry->flagA = (flags & 1) ? 1 : 0;
    entry->flagB = (flags & 2) ? 1 : 0;
}
