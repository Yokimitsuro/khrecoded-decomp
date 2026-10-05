#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    s32 kind;
    u8 pad_08[0x34];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

BOOL CanStartIdleRecord(s32 mode)
{
    BOOL result = FALSE;
    BOOL allowed = FALSE;

    if (!(data_ov031_020bc820->records[data_ov031_020bc820->recordIndex].kind == 1 || mode == 2)) {
        allowed = TRUE;
    }
    if (allowed && data_ov031_020bc820->nextRecordIndex == -1) {
        result = TRUE;
    }
    return result;
}
