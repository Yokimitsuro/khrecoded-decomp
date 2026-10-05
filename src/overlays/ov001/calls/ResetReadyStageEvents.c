#include "nitro/types.h"

typedef struct StageEventRecord {
    int kind;
    u8 pad_04[2];
    u16 lowFlags : 9;
    u16 usesSlotTable : 1;
    u16 highFlags : 6;
    u8 pad_08[6];
    u16 type;
    u16 isReady;
} StageEventRecord;

typedef struct StageData {
    u8 pad_00000[0x18de4];
    u16 eventCount;
} StageData;

extern StageData *func_ov001_020877d0(void);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern BOOL func_ov001_020645c8(u32 flag);
extern void ResetGroupLeaderAndSetState(StageEventRecord *record);
extern void ResetActorMotion(StageEventRecord *record, BOOL keepSpeed);

void ResetReadyStageEvents(void)
{
    StageData *stage = func_ov001_020877d0();
    int i;

    for (i = 0; i < stage->eventCount; i++) {
        StageEventRecord *record = GetStageEventRecord((u16)(i + 1));
        BOOL reset = TRUE;

        if (record == NULL || record->isReady == 0) {
            continue;
        }
        if (record->type == 99 && record->usesSlotTable) {
            continue;
        }
        if (record->kind == 2) {
            if (!func_ov001_020645c8(0x379c)) {
                reset = FALSE;
            }
        } else if (record->kind == 6) {
            reset = FALSE;
        }
        if (reset) {
            ResetGroupLeaderAndSetState(record);
            ResetActorMotion(record, TRUE);
        }
    }
}
