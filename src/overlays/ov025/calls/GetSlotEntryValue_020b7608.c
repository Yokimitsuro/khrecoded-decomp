#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 firstIndex;
    u16 index;
} SlotRecord;

typedef struct ValueEntry {
    u16 value;
    u16 unk_2;
    u32 unk_4;
} ValueEntry;

typedef struct ValueList {
    u8 pad_00[8];
    ValueEntry entries[1];
} ValueList;

typedef struct ValueTable {
    u8 pad_00[4];
    ValueList *list;
} ValueTable;

typedef struct SlotPanel {
    u8 pad_00[4];
    ValueTable *table;
    u8 pad_08[0x68];
    SlotRecord *slots[3];
} SlotPanel;

int GetSlotEntryValue_020b7608(SlotPanel *panel, int slot)
{
    ValueList *list = panel->table->list;

    if (slot < 0 || slot > 3) {
        return -1;
    }
    if (slot == 0) {
        if (panel->slots[0] == NULL) {
            return -1;
        }
        return list->entries[panel->slots[0]->firstIndex].value;
    }
    if (panel->slots[slot - 1] == NULL) {
        return -1;
    }
    return list->entries[panel->slots[slot - 1]->index].value;
}
