#include "nitro/types.h"

typedef struct StageEventRecord {
    int kind;
    u8 pad_04[0xa];
    u16 type;
    u16 isReady;
    u8 pad_12[0x5e];
    int value;
    u8 pad_74[0x13c];
    int pendingCount;
} StageEventRecord;

extern int data_ov001_0209f2e8;
extern StageEventRecord *GetStageEventRecord(u32 id);

int IsStageEventReady(u32 id)
{
    StageEventRecord *record;

    if (data_ov001_0209f2e8 != -1) {
        record = GetStageEventRecord(id);
        if (record != NULL) {
            if (record->type == 99) {
                return record->value;
            }
            if (record->kind == 2 && record->pendingCount > 0) {
                return 0;
            }
            if (record->isReady) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
