#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} RecordC;

typedef struct {
    u8 pad_00[0x5c];
    RecordC *tableC;
} RecordManager;

extern RecordManager *data_020613d0;

/* Gets a record table C entry. */
RecordC *GetRecordTableCEntry(s32 index)
{
    RecordManager *manager = data_020613d0;

    if (manager == 0) {
        return 0;
    }
    if (manager->tableC == 0) {
        return 0;
    }
    return manager->tableC + index;
}
