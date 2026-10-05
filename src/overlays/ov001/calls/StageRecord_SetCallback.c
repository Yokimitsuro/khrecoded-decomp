#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void *GetStageEventRecord(u32 id);
extern void SetActorCallbackPair(void *record, u32 callback, u32 userData);

void StageRecord_SetCallback(u32 id, u32 callback, u32 userData)
{
    void *record;

    if (id != 0 && data_ov001_0209f2e8 != -1 && (record = GetStageEventRecord(id)) != NULL) {
        SetActorCallbackPair(record, callback, userData);
    }
}
