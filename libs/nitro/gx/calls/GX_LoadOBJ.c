#include "libs/nitro/gx/gx_load_internal.h"

void GX_LoadOBJ(const void *source, u32 offset, u32 size)
{
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(0x06400000 + offset), size);
}
