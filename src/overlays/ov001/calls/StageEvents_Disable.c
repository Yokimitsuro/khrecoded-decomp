#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void LockStageSlotObjects(u32 eventIndex);

void StageEvents_Disable(u32 eventIndex)
{
    if (data_ov001_0209f2e8 != -1) {
        LockStageSlotObjects(eventIndex);
    }
}
