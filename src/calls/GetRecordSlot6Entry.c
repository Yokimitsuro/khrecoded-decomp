#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
    u8 *slot6;
} RecordManager;

extern RecordManager *gRecordManager;

/* Returns a pointer to record slot 6 entry. */
u8 *GetRecordSlot6Entry(int index)
{
    RecordManager *manager = gRecordManager;
    u8 *table;

    if (manager == NULL || (table = manager->slot6) == NULL) {
        return NULL;
    }
    return table + index * 0x10;
}
