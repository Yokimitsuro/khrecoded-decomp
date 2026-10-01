#include "libs/nitro/gx/gx_internal.h"

extern void PMi_SetDispOffCount(void);

void GX_DispOff(void)
{
    u32 displayControl = REG_GX_DISPCNT;

    gGXDataState.isDisplayOn = FALSE;
    gGXBssState.displayMode = (u16)((displayControl & GX_DISPCNT_DISPLAY_MODE_MASK) >> 16);
    REG_GX_DISPCNT = displayControl & ~GX_DISPCNT_DISPLAY_MODE_MASK;
    PMi_SetDispOffCount();
}