#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[6];
    u16 flagsLow : 8;
    u16 selectable : 1;
    u16 flagsHigh : 7;
    u8 pad_08[0x68];
    s32 activeCount;
} StageRecord;

typedef struct StageRecordRange {
    u8 pad_00[0xA];
    u16 first;
    s16 last;
} StageRecordRange;

extern StageRecord *GetStageEventRecord(u32 id);

u16 CountActiveStageRecords(StageRecordRange *range, BOOL selectableOnly)
{
    u16 index = range->first;
    u16 count = 0;
    StageRecord *record;

    for (; index <= range->last; index++) {
        record = GetStageEventRecord((u16)(index + 1));
        if (record != NULL && record->activeCount > 0) {
            if (!selectableOnly || record->selectable) {
                count++;
            }
        }
    }
    return count;
}
