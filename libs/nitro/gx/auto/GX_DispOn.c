#include "libs/nitro/gx/gx_internal.h"

void GX_DispOn(void)
{
    sIsDispOn = TRUE;
    if (sDispMode != GX_DISPMODE_OFF) {
        REG_GX_DISPCNT = (REG_GX_DISPCNT & ~GX_DISPCNT_DISPLAY_MODE_MASK)
                       | (sDispMode << 16);
    } else {
        REG_GX_DISPCNT |= GX_DISPMODE_GRAPHICS << 16;
    }
}