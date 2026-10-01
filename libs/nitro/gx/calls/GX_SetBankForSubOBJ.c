#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForSubOBJ -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForSubOBJ (GXVRamSubOBJ sub_obj)
{

	gGXState.vramCnt.lcdc = (u16)(~sub_obj & (gGXState.vramCnt.lcdc | gGXState.vramCnt.sub_obj));
	gGXState.vramCnt.sub_obj = sub_obj;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetSubOBJ_(sub_obj);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForSubOBJ (GXVRamSubOBJ sub_obj)
{
	GxSetBankForSubOBJ(sub_obj);
}
