#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void *GetStageEventRecord(u32 id);
extern BOOL func_ov001_02096644(void *record, u32 slot, void *outPoint);

BOOL StageRecord_GetSlotPosition(u32 id, u32 slot, void *outPoint)
{
    void *record;

    if (data_ov001_0209f2e8 != -1 && (record = GetStageEventRecord(id)) != NULL) {
        return func_ov001_02096644(record, slot, outPoint);
    }
    return FALSE;
}
