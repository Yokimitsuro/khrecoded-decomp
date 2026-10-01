#include "libs/nitro/gx/gx_state_internal.h"

#define REG_VRAMCNT_C (*(volatile u8 *)0x04000242)
#define REG_VRAMCNT_H (*(volatile u8 *)0x04000248)
#define REG_VRAMCNT_I (*(volatile u8 *)0x04000249)

extern void GX_VRAMCNT_SetLCDC_(u32 banks);

static inline void GX_VRAMCNT_SetSubBG_(s32 banks)
{
    switch (banks) {
    case 4:
        REG_VRAMCNT_C = 0x84;
        break;
    case 0x180:
        REG_VRAMCNT_I = 0x81;
    case 0x80:
        REG_VRAMCNT_H = 0x81;
        break;
    case 0:
        break;
    default:
        break;
    }
}

void GX_SetBankForSubBG(s32 banks)
{
    gGXState.vram.lcdc = (u16)(~banks & (gGXState.vram.lcdc | gGXState.vram.subBG));
    gGXState.vram.subBG = (u16)banks;

    GX_VRAMCNT_SetSubBG_(banks);
    GX_VRAMCNT_SetLCDC_(gGXState.vram.lcdc);
}
