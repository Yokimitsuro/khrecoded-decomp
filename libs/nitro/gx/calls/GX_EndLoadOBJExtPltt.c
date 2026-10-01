#include "libs/nitro/gx/gx_load_internal.h"
#include "libs/nitro/gx/gx_load_state_internal.h"

extern void MI_WaitDma(u32 channel);
extern void GX_SetBankForOBJExtPltt(GXVRamOBJExtPltt banks);

void GX_EndLoadOBJExtPltt(void)
{
    if (GXi_DmaId != (u32)-1) {
        MI_WaitDma(GXi_DmaId);
    }
    GX_SetBankForOBJExtPltt(gGXExtPlttLoadState.objExtPltt);
    gGXExtPlttLoadState.objExtPltt = 0;
    gGXExtPlttLoadState.objExtPlttLCDCBase = 0;
}
