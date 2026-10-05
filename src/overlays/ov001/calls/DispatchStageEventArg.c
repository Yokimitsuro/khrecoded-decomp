#include "nitro/types.h"

typedef struct StageEventRecord {
    u8 pad_000[6];
    u16 lowFlags : 9;
    u16 usesSlotTable : 1;
    u16 highFlags : 6;
    u8 pad_008[6];
    u16 type;
    u8 pad_010[0x1a7];
    u8 slotGroup : 2;
    u8 slotIndex : 6;
} StageEventRecord;

extern int data_ov001_0209f2e8;
extern StageEventRecord *GetStageEventRecord(u32 id);
extern int func_ov016_020a6df8(u32 group, u32 index, int arg);
extern int func_ov001_0209591c(StageEventRecord *record, int arg);

int DispatchStageEventArg(u32 id, int arg)
{
    StageEventRecord *record;

    if (data_ov001_0209f2e8 != -1 && id != 0) {
        record = GetStageEventRecord(id);
        if (record != NULL) {
            if (record->type == 99 && record->usesSlotTable) {
                return func_ov016_020a6df8(record->slotGroup, record->slotIndex, arg);
            }
            return func_ov001_0209591c(record, arg);
        }
    }
    return 0;
}
