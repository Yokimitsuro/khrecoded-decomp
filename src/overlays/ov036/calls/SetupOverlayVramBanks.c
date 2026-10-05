#include "nitro/types.h"

extern void ResetDisplayHardware(void);
extern void GX_SetBankForLCDC(int bank);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void GX_DisableBankForLCDC(void);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForSubOBJ(int bank);

#define REG_DISPCNT (*(vu32 *)0x04000000)

void SetupOverlayVramBanks(void)
{
    ResetDisplayHardware();
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    GX_DisableBankForLCDC();
    GX_SetBankForBG(8);
    GX_SetBankForBGExtPltt(0);
    GX_SetBankForOBJ(0x10);
    GX_SetBankForOBJExtPltt(0);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x100010;
    GX_SetGraphicsMode(1, 0, 1);
    GX_SetBankForSubOBJ(0x100);
}
