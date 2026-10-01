#include "libs/nitro/gx/gx_state_internal.h"

extern void GX_VRAMCNT_SetLCDC_(u32 banks);

void GX_SetBankForLCDC(u32 banks)
{
    gGXState.vram.lcdc |= (u16)banks;
    GX_VRAMCNT_SetLCDC_(banks);
}