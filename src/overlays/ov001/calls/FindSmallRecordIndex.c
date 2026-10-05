#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03 : 4;
    u8 kind : 4;
    u8 pad_04[8];
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

u16 FindSmallRecordIndex(u32 id)
{
    SmallRecordTable *table = data_ov001_020a0528->table;
    u16 index;

    for (index = 0; index < table->count; index++) {
        SmallRecord *record = &table->entries[index];
        if (record->kind == 0 && record->id == id) {
            return index;
        }
    }
    return 0xffff;
}
