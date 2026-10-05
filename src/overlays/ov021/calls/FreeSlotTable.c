#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad00[0x2c];
} SlotRecord;

typedef struct SlotTable {
    SlotRecord *records;
    s32 count;
    s8 *ids;
} SlotTable;

extern void func_ov021_020a90a4(SlotRecord *record);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void FreeSlotTable(SlotTable *table)
{
    int i;

    if (table->count > 0) {
        for (i = 0; i < table->count; i++) {
            if (table->ids[i] >= 0) {
                func_ov021_020a90a4(&table->records[i]);
            }
        }
        NNSi_FndFreeFromDefaultHeap(table->records);
        table->count = 0;
        NNSi_FndFreeFromDefaultHeap(table->ids);
    }
}
