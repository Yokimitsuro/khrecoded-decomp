#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForSubBGExtPltt -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForSubBGExtPltt (GXVRamSubBGExtPltt sub_bgExtPltt)
{

	gGXState.vramCnt.lcdc = (u16)(~sub_bgExtPltt & (gGXState.vramCnt.lcdc | gGXState.vramCnt.sub_bgExtPltt));
	gGXState.vramCnt.sub_bgExtPltt = sub_bgExtPltt;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetSubBGExtPltt_(sub_bgExtPltt);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForSubBGExtPltt (GXVRamSubBGExtPltt sub_bgExtPltt)
{
	GxSetBankForSubBGExtPltt(sub_bgExtPltt);
}
