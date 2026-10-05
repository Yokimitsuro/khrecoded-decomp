#include "nitro/types.h"

typedef struct {
    u8 data[0x18];
} RecordB;

typedef struct {
    u8 pad_00[0x54];
    RecordB *tableB;
} RecordManager;

extern RecordManager *gRecordManager;

/* Gets a record table B entry. */
RecordB *GetRecordTableBEntry(s32 index)
{
    RecordManager *manager = gRecordManager;

    if (manager == 0) {
        return 0;
    }
    if (manager->tableB == 0) {
        return 0;
    }
    return manager->tableB + index;
}
