#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForOBJ -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForOBJ (GXVRamOBJ obj)
{

	gGXState.vramCnt.lcdc = (u16)(~obj & (gGXState.vramCnt.lcdc | gGXState.vramCnt.obj));
	gGXState.vramCnt.obj = obj;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetOBJ_(obj);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForOBJ (GXVRamOBJ obj)
{
	GxSetBankForOBJ(obj);
}
