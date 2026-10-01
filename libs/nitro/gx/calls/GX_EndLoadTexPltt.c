#include "libs/nitro/gx/gx_load_internal.h"
#include "libs/nitro/gx/gx_load_state_internal.h"

extern void MI_WaitDma(u32 channel);
extern void GX_SetBankForTexPltt(GXVRamTexPltt banks);

void GX_EndLoadTexPltt(void)
{
    if (GXi_DmaId != (u32)-1) {
        MI_WaitDma(GXi_DmaId);
    }
    GX_SetBankForTexPltt(gGXTextureLoadState.texPltt);
    gGXTextureLoadState.texPltt = 0;
    gGXTextureLoadState.texPlttLCDCBase = 0;
}
