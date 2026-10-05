#include "nitro/types.h"

extern u32 data_ov038_020bd164;

void ResetOv038ExitState(u32 mode)
{
    u32 context;

    context = data_ov038_020bd164;
    *(u32 *)(context + 0xd0a0) = mode;
    *(u32 *)(context + 0xd0a4) = 0;
    *(u32 *)(context + 0xd0a8) = 0;
}
