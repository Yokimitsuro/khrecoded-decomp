#include "nitro/types.h"

typedef struct {
    u32 handle;
    u16 group;
    u16 channel;
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
extern void func_ov001_020688d4(u32 handle, int enable, int arg2);
extern void CallIfSessionActive_02087ec0(u32 handle, u16 channel);
extern void CallIfSessionActive_02087edc(u32 handle, u16 group, int arg2);

void RestoreActiveRecordItems(void)
{
    ActiveRecord *record;
    int i = 0;

    record = &data_ov031_020bc820->records[data_ov031_020bc820->recordIndex];
    for (; i < record->itemCount; i++) {
        func_ov001_0206890c(record->items[i].handle);
        func_ov001_020688d4(record->items[i].handle, 1, 0);
        CallIfSessionActive_02087ec0(record->items[i].handle, record->items[i].channel);
        CallIfSessionActive_02087edc(record->items[i].handle, record->items[i].group, -1);
    }
}
