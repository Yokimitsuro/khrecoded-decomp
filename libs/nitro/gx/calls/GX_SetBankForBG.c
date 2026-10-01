#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForBG -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForBG (GXVRamBG bg)
{

	gGXState.vramCnt.lcdc = (u16)(~bg & (gGXState.vramCnt.lcdc | gGXState.vramCnt.bg));
	gGXState.vramCnt.bg = bg;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetBG_(bg);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForBG (GXVRamBG bg)
{
	GxSetBankForBG(bg);
}
