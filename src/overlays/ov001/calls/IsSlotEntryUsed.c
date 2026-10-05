#include "nitro/types.h"

typedef struct SlotEntry {
    u32 flags;
    u8 data[8];
} SlotEntry;

typedef struct SlotTable {
    SlotEntry *entries;
} SlotTable;

u16 IsSlotEntryUsed(SlotTable *table, int slot)
{
    return (table->entries[(u16)(slot - 1)].flags & 1) ? 1 : 0;
}
