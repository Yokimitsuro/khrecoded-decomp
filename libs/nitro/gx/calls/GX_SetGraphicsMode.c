#include "libs/nitro/gx/gx_internal.h"

void GX_SetGraphicsMode(GXDispMode displayMode, GXBGMode bgMode, GXBG0As bg0Mode)
{
    u32 displayControl = REG_GX_DISPCNT;

    gGXBssState.displayMode = (u16)displayMode;
    if (!gGXDataState.isDisplayOn) {
        displayMode = GX_DISPMODE_OFF;
    }

    displayControl &= ~(GX_DISPCNT_BG_MODE_MASK
                      | GX_DISPCNT_BG0_3D_MASK
                      | GX_DISPCNT_DISPLAY_MODE_MASK
                      | GX_DISPCNT_VRAM_BLOCK_MASK);
    REG_GX_DISPCNT = displayControl
                   | (displayMode << 16)
                   | bgMode
                   | (bg0Mode << 3);

    if (gGXBssState.displayMode == GX_DISPMODE_OFF) {
        gGXDataState.isDisplayOn = FALSE;
    }
}