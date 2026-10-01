#include "libs/nitro/gx/gx_load_internal.h"
#include "libs/nitro/gx/gx_load_state_internal.h"

extern void MI_WaitDma(u32 channel);
extern void GX_SetBankForTex(GXVRamTex banks);

void GX_EndLoadTex(void)
{
    if (GXi_DmaId != (u32)-1) {
        MI_WaitDma(GXi_DmaId);
    }
    GX_SetBankForTex(gGXTextureLoadState.tex);
    gGXTextureLoadState.texBlock1Size = 0;
    gGXTextureLoadState.texLCDCBase2 = 0;
    gGXTextureLoadState.texLCDCBase1 = 0;
    gGXTextureLoadState.tex = 0;
}
