#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} SmallRecord;

typedef struct {
    u8 count;
    u8 pad_01[3];
    SmallRecord *entries;
} SmallRecordTable;

typedef struct {
    u8 pad_00[0x18df8];
    SmallRecordTable *table;
} OverlayState;

extern OverlayState *data_ov001_020a0528;

SmallRecord *GetSmallTableEntry(int index)
{
    SmallRecordTable *table;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    table = data_ov001_020a0528->table;
    if (table == 0) {
        return 0;
    }
    if (index < table->count) {
        return table->entries + index;
    }
    return 0;
}
