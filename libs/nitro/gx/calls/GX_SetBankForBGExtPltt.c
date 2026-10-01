#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForBGExtPltt -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForBGExtPltt (GXVRamBGExtPltt bgExtPltt)
{

	gGXState.vramCnt.lcdc = (u16)(~bgExtPltt & (gGXState.vramCnt.lcdc | gGXState.vramCnt.bgExtPltt));
	gGXState.vramCnt.bgExtPltt = bgExtPltt;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetBGEXTPLTT_(bgExtPltt);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForBGExtPltt (GXVRamBGExtPltt bgExtPltt)
{
	GxSetBankForBGExtPltt(bgExtPltt);
}
