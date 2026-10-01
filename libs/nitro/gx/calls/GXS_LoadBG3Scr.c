#include "libs/nitro/gx/gx_load_internal.h"

extern void *G2S_GetBG3ScrPtr(void);

void GXS_LoadBG3Scr(const void *source, u32 offset, u32 size)
{
    u32 base = (u32)G2S_GetBG3ScrPtr();
    GXi_DmaCopy16(GXi_DmaId, source, (void *)(base + offset), size);
}
