#include "nitro/types.h"

extern u32 GetStageActor();

u32 FindRecordById_0209c304(int id)
{
    u32 record;

    if (id == 0) {
        return 0;
    }
    record = GetStageActor((int)(short)id);
    return record;
}
