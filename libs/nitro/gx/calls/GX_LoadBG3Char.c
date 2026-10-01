#include "libs/nitro/gx/gx_load_internal.h"

extern void *G2_GetBG3CharPtr(void);

void GX_LoadBG3Char(const void *source, u32 offset, u32 size)
{
    u32 base = (u32)G2_GetBG3CharPtr();
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(base + offset), size);
}
