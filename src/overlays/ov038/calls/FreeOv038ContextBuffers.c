#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern int ZeroHalfThenFree(void *arg0);

void FreeOv038ContextBuffers(void)
{
    u32 context;
    s32 index;

    context = data_ov038_020bd164;
    index = 0;
    do {
        ZeroHalfThenFree((void *)*(u32 *)(context + index * 4 + 4));
        index = index + 1;
    } while (index < 3);
}
