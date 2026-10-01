#include "libs/nitro/gx/gx_load_internal.h"

void GXS_LoadOBJ(const void *source, u32 offset, u32 size)
{
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(0x06600000 + offset), size);
}
