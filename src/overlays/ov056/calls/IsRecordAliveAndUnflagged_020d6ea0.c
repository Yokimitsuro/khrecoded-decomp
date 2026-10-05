#include "nitro/types.h"

typedef struct StageRecordInfo {
    u16 unk_00;
    u16 unk_02_0 : 1;
    u16 isFlagged : 1;
    u16 unk_02_2 : 14;
    u8 pad_04[0x20];
} StageRecordInfo;

extern BOOL func_ov001_02087988(u32 id, StageRecordInfo *info);
extern BOOL StageRecord_IsDefeated(u32 id);

BOOL IsRecordAliveAndUnflagged_020d6ea0(u32 id)
{
    StageRecordInfo info;

    if (func_ov001_02087988(id, &info)) {
        if (!info.isFlagged && !StageRecord_IsDefeated(id)) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
