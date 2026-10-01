#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForSubOBJExtPltt -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForSubOBJExtPltt (GXVRamSubOBJExtPltt sub_objExtPltt)
{

	gGXState.vramCnt.lcdc = (u16)(~sub_objExtPltt & (gGXState.vramCnt.lcdc | gGXState.vramCnt.sub_objExtPltt));
	gGXState.vramCnt.sub_objExtPltt = sub_objExtPltt;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetSubOBJExtPltt_(sub_objExtPltt);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForSubOBJExtPltt (GXVRamSubOBJExtPltt sub_objExtPltt)
{
	GxSetBankForSubOBJExtPltt(sub_objExtPltt);
}
