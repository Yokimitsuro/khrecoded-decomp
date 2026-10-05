#include "nitro/types.h"

typedef struct {
    u8 data[0x40];
} RecordD;

typedef struct {
    u8 pad_00[0x64];
    RecordD *tableD;
} RecordManager;

extern RecordManager *gRecordManager;

/* Gets a record table D entry. */
RecordD *GetRecordTableDEntry(s32 index)
{
    RecordManager *manager = gRecordManager;

    if (manager == 0) {
        return 0;
    }
    if (manager->tableD == 0) {
        return 0;
    }
    return manager->tableD + index;
}
