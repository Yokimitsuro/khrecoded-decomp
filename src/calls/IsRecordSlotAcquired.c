#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 refCounts[1];
} RecordManager;

extern RecordManager *gRecordManager;

/* Checks whether a record slot is in use. */
BOOL IsRecordSlotAcquired(s32 slot)
{
    RecordManager *manager = gRecordManager;

    if (manager == 0 || manager->refCounts[slot] == 0) {
        return FALSE;
    }
    return TRUE;
}
