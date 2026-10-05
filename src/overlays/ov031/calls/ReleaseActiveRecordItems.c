#include "nitro/types.h"

typedef struct {
    u32 handle;
    u32 extra;
} RecordItem;

typedef struct {
    u8 pad_00[0x30];
    RecordItem *items;
    u8 pad_34[0x6];
    u8 itemCount;
    u8 pad_3b;
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[0x8];
    ActiveRecord *records;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void func_ov001_0206890c(u32 handle);

void ReleaseActiveRecordItems(void)
{
    ActiveRecord *record;
    int i = 0;

    record = &data_ov031_020bc820->records[data_ov031_020bc820->recordIndex];

    for (; i < record->itemCount; i++) {
        func_ov001_0206890c(record->items[i].handle);
    }
}

