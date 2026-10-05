#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x70];
    s32 hitPoints;
} StageRecord;

extern int data_ov001_0209f2e8;
extern StageRecord *func_ov001_0209c114(u32 id);

BOOL StageRecord_IsDefeated(u32 id)
{
    StageRecord *record;

    if (data_ov001_0209f2e8 != -1 && (record = func_ov001_0209c114(id)) != NULL) {
        if (record->hitPoints == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
