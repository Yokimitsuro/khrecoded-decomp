#include "nitro/types.h"

#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000A)
#define REG_BG2CNT (*(vu16 *)0x0400000C)
#define REG_BG3CNT (*(vu16 *)0x0400000E)
#define REG_BLDCNT (*(vu16 *)0x04000050)
#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)

extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As3d);
extern void GX_SetBankForBGExtPltt(int bank);

void SetupFieldBgLayers(void)
{
    GX_SetGraphicsMode(1, 0, 1);
    GX_SetBankForBGExtPltt(0);
    REG_BG1CNT = (REG_BG1CNT & 0x43) | 0x1F00;
    REG_BG2CNT = (REG_BG2CNT & 0x43) | 0x1E08;
    REG_BG3CNT = (REG_BG3CNT & 0x43) | 0x1D00;
    REG_BG0CNT = (REG_BG0CNT & ~3) | 3;
    REG_BG3CNT = (REG_BG3CNT & ~3) | 2;
    REG_BG2CNT = (REG_BG2CNT & ~3) | 1;
    REG_BG1CNT = (REG_BG1CNT & ~3) | 0;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x300010) | 0x10;
    REG_BLDCNT = 0;
}
