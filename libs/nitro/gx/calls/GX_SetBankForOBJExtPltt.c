#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForOBJExtPltt -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForOBJExtPltt (GXVRamOBJExtPltt objExtPltt)
{

	gGXState.vramCnt.lcdc = (u16)(~objExtPltt & (gGXState.vramCnt.lcdc | gGXState.vramCnt.objExtPltt));
	gGXState.vramCnt.objExtPltt = objExtPltt;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetOBJEXTPLTT_(objExtPltt);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForOBJExtPltt (GXVRamOBJExtPltt objExtPltt)
{
	GxSetBankForOBJExtPltt(objExtPltt);
}
