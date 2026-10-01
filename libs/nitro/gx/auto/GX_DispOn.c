#include "libs/nitro/gx/gx_internal.h"

void GX_DispOn(void)
{
    gGXDataState.isDisplayOn = TRUE;
    if (gGXBssState.displayMode != GX_DISPMODE_OFF) {
        REG_GX_DISPCNT = (REG_GX_DISPCNT & ~GX_DISPCNT_DISPLAY_MODE_MASK)
                       | (gGXBssState.displayMode << 16);
    } else {
        REG_GX_DISPCNT |= GX_DISPMODE_GRAPHICS << 16;
    }
}