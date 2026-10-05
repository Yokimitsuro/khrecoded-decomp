#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3a];
    u8 itemCount;
    u8 pad_3b;
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern s32 func_ov001_02063a4c(void);

BOOL CanLeaveActiveRecord(void)
{
    OverlayState *state = data_ov031_020bc820;

    if (state->recordIndex == -1) {
        return TRUE;
    }
    if (state->records[state->nextRecordIndex].itemCount != 0
        && (func_ov001_02063a4c() == 7 || func_ov001_02063a4c() == 8)) {
        return FALSE;
    }
    return TRUE;
}
