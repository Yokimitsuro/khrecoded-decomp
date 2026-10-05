#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 parent;
    u16 index;
} SlotRecord;

typedef struct SlotTable {
    u8 pad_00[6];
    u16 count;
    SlotRecord *records[1];
} SlotTable;

typedef struct ListData {
    u8 pad_00[8];
    SlotTable *slotTable;
} ListData;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    u8 pad_08[0x68];
    SlotRecord *slots[3];
    u8 pad_7c[4];
    u8 *entryStates;
    u8 *recordFlags;
} ListView;

void RebuildSlotChain(ListView *list, int slot, SlotRecord **preferred)
{
    SlotRecord *record;
    BOOL found;
    int i;
    SlotRecord *wanted;
    int index;
    u8 state;
    int parent;
    SlotTable *table = list->data->slotTable;

    parent = (slot == 0) ? 0 : list->slots[slot - 1]->index;
    for (; slot < 3; slot++) {
        found = FALSE;
        if (preferred != NULL && (wanted = preferred[slot]) != NULL) {
            for (i = 0; i < table->count; i++) {
                record = table->records[i];
                index = record->index;
                if (parent == record->parent && index == wanted->index) {
                    list->slots[slot] = record;
                    list->entryStates[index] = 0;
                    parent = index;
                    found = TRUE;
                    break;
                }
            }
        }
        if (!found) {
            found = FALSE;
            for (i = 0; i < table->count; i++) {
                record = table->records[i];
                index = record->index;
                state = list->entryStates[index];
                if (parent == record->parent && state <= 1 && list->recordFlags[i] != 2) {
                    list->slots[slot] = record;
                    list->entryStates[index] = 0;
                    parent = index;
                    found = TRUE;
                    break;
                }
            }
            if (!found) {
                for (; slot < 3; slot++) {
                    list->slots[slot] = NULL;
                }
                return;
            }
        }
    }
}
