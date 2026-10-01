#include "libs/nitro/gx/gx_load_internal.h"

extern void *G2S_GetBG1ScrPtr(void);

void GXS_LoadBG1Scr(const void *source, u32 offset, u32 size)
{
    u32 base = (u32)G2S_GetBG1ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, source, (void *)(base + offset), size);
}
