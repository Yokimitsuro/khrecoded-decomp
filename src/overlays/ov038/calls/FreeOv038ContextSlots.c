#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern int NNSi_FndFreeFromDefaultHeap();

void FreeOv038ContextSlots(void)
{
    u32 context;
    s32 index;

    context = data_ov038_020bd164;
    index = 0;
    do {
        if (*(s32 *)(context + index * 0x10 + 0x10) != 0) {
            NNSi_FndFreeFromDefaultHeap();
        }
        index = index + 1;
    } while (index < 3);
}
