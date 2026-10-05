#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern void NNS_FndInitListWithOffset0_0204f130(void *list);

void InitOv038SlotPools(void)
{
    u32 pool;
    s32 index;

    index = 0;
    pool = data_ov038_020bd164 + 0x40;
    do {
        NNS_FndInitListWithOffset0_0204f130((void *)(index * 0x6434 + pool));
        index = index + 1;
    } while (index < 2);
}
