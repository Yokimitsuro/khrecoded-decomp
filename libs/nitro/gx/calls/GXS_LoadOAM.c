#include "libs/nitro/gx/gx_load_internal.h"

void GXS_LoadOAM(const void *source, u32 offset, u32 size)
{
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(0x07000400 + offset), size);
}
