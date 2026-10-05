#include "nitro/types.h"

typedef struct GfxRegs {
    u32 dispcnt;
    u8 pad_04[4];
    u16 bg0cnt;
    u16 bg1cnt;
    u16 bg2cnt;
    u16 bg3cnt;
} GfxRegs;

extern void GX_SetBankForBG(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As3d);
extern void GX_SetBankForBGExtPltt(int bank);

void SetupMainBgLayers(void)
{
    volatile GfxRegs *regs;

    GX_SetBankForBG(0x10);
    regs = (volatile GfxRegs *)0x04000000;
    regs->dispcnt = (regs->dispcnt & ~0x1f00) | 0xd00;
    GX_SetGraphicsMode(1, 0, 1);
    GX_SetBankForBGExtPltt(0);
    regs->bg2cnt = (regs->bg2cnt & 0x43) | 0x1e08;
    regs->bg3cnt = (regs->bg3cnt & 0x43) | 0x1f00;
    regs->bg0cnt = (regs->bg0cnt & ~3) | 3;
    regs->bg2cnt = regs->bg2cnt & ~3;
    regs->bg3cnt = (regs->bg3cnt & ~3) | 1;
}
