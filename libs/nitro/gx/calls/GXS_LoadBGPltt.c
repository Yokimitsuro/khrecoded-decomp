#include "libs/nitro/gx/gx_load_internal.h"

void GXS_LoadBGPltt(const void *source, u32 offset, u32 size)
{
    GXi_DmaCopy16(GXi_DmaId, source, (void *)(0x05000400 + offset), size);
}
