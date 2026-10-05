#include "nitro/types.h"

typedef struct SlotEntry {
    u8 unknown_00[0x44];
    void *buffer;
} SlotEntry;

typedef struct SlotTable {
    u8 count;
    SlotEntry *entries;
    void *extra;
} SlotTable;

typedef struct MovieWork {
    u8 unknown_00[0xbc];
    SlotTable table;
} MovieWork;

extern MovieWork *data_ov035_020bc500;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeMovieSlotBuffers(void) {
    SlotTable *table = &data_ov035_020bc500->table;
    int i;

    if (table->entries != NULL) {
        for (i = 0; i < table->count; i++) {
            if (table->entries[i].buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap(table->entries[i].buffer);
            }
        }
        NNSi_FndFreeFromDefaultHeap(table->entries);
        table->entries = NULL;
    }
    if (table->extra != NULL) {
        NNSi_FndFreeFromDefaultHeap(table->extra);
        table->extra = NULL;
    }
}
