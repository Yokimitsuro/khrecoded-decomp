#include "libs/nitro/gx/gx_load_internal.h"

extern void *G2S_GetBG1CharPtr(void);

void GXS_LoadBG1Char(const void *source, u32 offset, u32 size)
{
    u32 base = (u32)G2S_GetBG1CharPtr();
    GXi_DmaCopy32(GXi_DmaId, source, (void *)(base + offset), size);
}
