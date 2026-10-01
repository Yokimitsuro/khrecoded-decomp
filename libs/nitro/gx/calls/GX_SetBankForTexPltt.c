#include "libs/nitro/gx/gx_state_internal.h"

extern void GX_VRAMCNT_SetLCDC_(u32 banks);

static inline void writeE(u8 value) { *(volatile u8 *)0x04000244 = value; }
static inline void writeF(u8 value) { *(volatile u8 *)0x04000245 = value; }
static inline void writeG(u8 value) { *(volatile u8 *)0x04000246 = value; }

void GX_SetBankForTexPltt(s32 banks)
{
    gGXState.vram.lcdc = (u16)((gGXState.vram.lcdc | gGXState.vram.texPltt) & ~banks);
    gGXState.vram.texPltt = (u16)banks;

    switch (banks) {
    case 0:
        break;
    case 0x60:
        writeG(0x8b);
    case 0x20:
        writeF(0x83);
        break;
    case 0x40:
        writeG(0x83);
        break;
    case 0x70:
        writeG(0x9b);
    case 0x30:
        writeF(0x93);
    case 0x10:
        writeE(0x83);
        break;
    }

    GX_VRAMCNT_SetLCDC_(gGXState.vram.lcdc);
}
