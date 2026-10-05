#include "nitro/types.h"

extern void ResetDisplayHardware(void);
extern void GX_SetBankForTex(int bank);
extern void GX_SetBankForTexPltt(int bank);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void NNS_GfdInitFrmTexVramManager(int numSlot, BOOL useAsDefault);
extern void NNS_GfdInitFrmPlttVramManager(int size, BOOL useAsDefault);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GXS_SetGraphicsMode(int bgMode);
extern void G2x_SetBlendAlpha_(vu32 *reg, int plane1, int plane2, int ev1, int ev2);

#define REG_DISPCNT      (*(vu32 *)0x04000000)
#define REG_BG0CNT       (*(vu16 *)0x04000008)
#define REG_BG1CNT       (*(vu16 *)0x0400000a)
#define REG_DB_DISPCNT   (*(vu32 *)0x04001000)
#define REG_DB_BG1CNT    (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT    (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT    (*(vu16 *)0x0400100e)
#define REG_DB_BLDCNT    ((vu32 *)0x04001050)

void SetupDisplayBanksAndLayers(void)
{
    ResetDisplayHardware();
    GX_SetBankForTex(3);
    GX_SetBankForTexPltt(0x60);
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    GX_SetBankForOBJExtPltt(0);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJExtPltt(0);
    NNS_GfdInitFrmTexVramManager(2, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);
    GX_SetGraphicsMode(1, 0, 1);

    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (0 << 14) | (1 << 7) | (0 << 8) | (1 << 2));
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 0);
    REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 1);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (3 << 8);

    GXS_SetGraphicsMode(0);

    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | (1 << 14) | (1 << 7) | (0 << 8) | (1 << 2));
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | (1 << 14) | (1 << 7) | (2 << 8) | (1 << 2));
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & 0x43) | (0 << 14) | (0 << 7) | (4 << 8) | (1 << 2));
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x300010) | 0x10;
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & ~3) | 3);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & ~3) | 2);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & ~3) | 1);

    G2x_SetBlendAlpha_(REG_DB_BLDCNT, 0x10, 0x22, 0, 0x10);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (0x12 << 8);
}
