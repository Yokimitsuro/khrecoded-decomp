#include "nitro/types.h"

typedef struct {
    u16 field0;
    u16 field1;
    u32 handle;
} ResourceSlot;

extern ResourceSlot *GetStageEntrySlot();
extern u32 StopSoundSeqHandle();
extern u32 func_0204dc50();

void ReleaseSlotResource(void)
{
    ResourceSlot *slot;
    u32 flag;

    slot = GetStageEntrySlot();
    if ((slot != 0) && (slot->handle != 0)) {
        flag = func_0204dc50();
        if (flag != 0) {
            StopSoundSeqHandle(slot->handle);
        }
        slot->handle = 0;
        slot->field0 = 0;
        slot->field1 = 0;
    }
}
