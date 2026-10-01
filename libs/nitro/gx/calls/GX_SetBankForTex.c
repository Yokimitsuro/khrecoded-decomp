#include "libs/nitro/gx/gx_vramcnt_internal.h"

/* GX_SetBankForTex -- NitroSDK gx_vramcnt.c: map the banks to this use, the rest back to LCDC. */
static inline void GxSetBankForTex (GXVRamTex tex)
{

	gGXState.vramCnt.lcdc = (u16)(~tex & (gGXState.vramCnt.lcdc | gGXState.vramCnt.tex));
	gGXState.vramCnt.tex = tex;

	GX_StateCheck_VRAMCnt();

	GX_VRAMCNT_SetTEX_(tex);
	GX_VRAMCNT_SetLCDC_(gGXState.vramCnt.lcdc);
}

void GX_SetBankForTex (GXVRamTex tex)
{
	GxSetBankForTex(tex);
}
