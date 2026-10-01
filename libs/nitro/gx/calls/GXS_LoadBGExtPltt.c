#include "libs/nitro/gx/gx_load_internal.h"

void GXS_LoadBGExtPltt(const void *source, u32 offset, u32 size)
{
    GXi_DmaCopy32Async(GXi_DmaId, source,
                       (void *)(0x06898000 + offset), size, 0, 0);
}
