#include "libs/nitro/gx/gx_load_internal.h"

extern void *G2_GetBG2CharPtr(void);

void GX_LoadBG2Char(const void *source, u32 offset, u32 size)
{
    u32 base = (u32)G2_GetBG2CharPtr();
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(base + offset), size);
}
