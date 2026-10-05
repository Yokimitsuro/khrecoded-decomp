#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern void ReleaseOv038SlotPools(void);
extern void FreeOv038ContextSlots(void);
extern void FreeOv038ContextBuffers(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseOv038Context(void)
{
    u32 context;

    context = data_ov038_020bd164;
    ReleaseOv038SlotPools();
    FreeOv038ContextSlots();
    FreeOv038ContextBuffers();
    NNSi_FndFreeFromDefaultHeap((void *)context);
    data_ov038_020bd164 = 0;
}
