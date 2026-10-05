#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x10];
    int value;
} SlotEntry;

typedef struct SlotTable {
    u8 pad_00[8];
    SlotEntry *entries[1];
} SlotTable;

typedef struct SlotManager {
    SlotTable *table;
    u8 pad_004[0x10bc];
    s8 overrideIndex;
    u8 pad_10c1[3];
    int overrideValue;
} SlotManager;

extern SlotManager *data_ov001_020a048c;

int GetSlotEntryValue(int index)
{
    SlotManager *manager = data_ov001_020a048c;
    SlotEntry *entry = manager->table->entries[index];

    if (index == manager->overrideIndex) {
        return manager->overrideValue;
    }
    return entry->value;
}
