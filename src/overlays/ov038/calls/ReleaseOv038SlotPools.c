#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern void Slot_UnlinkAll(void *p);
extern int Obj_Release(void *object);

void ReleaseOv038SlotPools(void)
{
    u32 pool;
    s32 index;

    index = 0;
    pool = data_ov038_020bd164 + 0x40;
    do {
        Slot_UnlinkAll((void *)(pool + index * 0x6434));
        Obj_Release((void *)(pool + index * 0x6434));
        index = index + 1;
    } while (index < 2);
}
