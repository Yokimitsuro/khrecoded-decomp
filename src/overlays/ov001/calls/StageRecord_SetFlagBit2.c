#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x4];
    u16 flags;
} StageRecord;

extern int data_ov001_0209f2e8;
extern StageRecord *func_ov001_0209c114(u32 id);

void StageRecord_SetFlagBit2(u32 id)
{
    StageRecord *record;

    if (id != 0 && data_ov001_0209f2e8 != -1 && (record = func_ov001_0209c114(id)) != NULL) {
        record->flags |= 4;
    }
}
