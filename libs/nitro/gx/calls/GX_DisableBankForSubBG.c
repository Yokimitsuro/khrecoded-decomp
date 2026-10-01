#include "libs/nitro/gx/gx_state_internal.h"

extern u32 disableBankForX_(u16 *bankState);

u32 GX_DisableBankForSubBG(void)
{
    return disableBankForX_(&gGXState.vram.subBG);
}
