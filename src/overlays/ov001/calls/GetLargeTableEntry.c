#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} LargeRecord;

typedef struct {
    u8 pad_00[2];
    u16 count;
    u8 pad_04[4];
    LargeRecord *entries;
} LargeRecordTable;

typedef struct {
    u8 pad_00[0x18df8];
    LargeRecordTable *table;
} OverlayState;

extern OverlayState *data_ov001_020a0528;

LargeRecord *GetLargeTableEntry(u32 index)
{
    LargeRecordTable *table;

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
