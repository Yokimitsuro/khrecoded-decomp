#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad00[8];
    u8 data[0x24];
} SlotRecord;

typedef struct SlotTable {
    SlotRecord *records;
    s32 count;
    s8 *ids;
} SlotTable;

void *FindSlotRecordById(SlotTable *table, int id, int *outIndex)
{
    void *found = NULL;
    int i;

    if (outIndex != NULL) {
        *outIndex = -1;
    }
    for (i = 0; i < table->count; i++) {
        if (id == table->ids[i]) {
            found = table->records[i].data;
            if (outIndex != NULL) {
                *outIndex = i;
            }
            break;
        }
    }
    return found;
}
