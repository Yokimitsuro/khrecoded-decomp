#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 refCounts[1];
} RecordManager;

extern RecordManager *data_020613d0;

/* Checks whether a record slot is in use. */
BOOL IsRecordSlotAcquired(s32 slot)
{
    RecordManager *manager = data_020613d0;

    if (manager == 0 || manager->refCounts[slot] == 0) {
        return FALSE;
    }
    return TRUE;
}
