#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x5];
    s8 slotId;
    u8 pad_06[0x2];
} SlotEntry;

typedef struct SlotTable {
    u8 pad_00[0x60];
    SlotEntry *entries;
    u8 pad_64[0x18];
    u8 entryCount;
    u8 pad_7D;
    s8 activeSlotId;
} SlotTable;

SlotEntry *FindActiveSlotEntry(SlotTable *table)
{
    u8 entryIndex;
    u8 entryCount = table->entryCount;
    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
        if (table->activeSlotId == table->entries[entryIndex].slotId) {
            return &table->entries[entryIndex];
        }
    }
    return NULL;
}
