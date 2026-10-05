#include "nitro/types.h"

#define REG_DISPCNT    (*(vu32 *)0x04000000)
#define REG_BG0CNT     (*(vu16 *)0x04000008)
#define REG_BG1CNT     (*(vu16 *)0x0400000a)
#define REG_BG2CNT     (*(vu16 *)0x0400000c)
#define REG_BG3CNT     (*(vu16 *)0x0400000e)
#define REG_POWCNT     (*(vu16 *)0x04000304)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT  (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT  (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT  (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT  (*(vu16 *)0x0400100e)

extern void ResetDisplayHardware(void);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetSecondaryBrightness(int brightness);
extern void GX_SetBankForLCDC(int bank);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void GX_DisableBankForLCDC(void);
extern void TaskManager_SetEnabled(int value);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GXS_SetGraphicsMode(int bgMode);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void GX_SetBankForSubOBJ(int bank);

void SetupRecordMenuDisplay(void)
{
    ResetDisplayHardware();
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    GX_DisableBankForLCDC();
    REG_POWCNT |= 0x8000;
    TaskManager_SetEnabled(0);

    GX_SetGraphicsMode(1, 0, 0);
    GX_SetBankForBG(2);
    GX_SetBankForBGExtPltt(0x10);
    GX_SetBankForOBJ(1);
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x100010;
    REG_BG0CNT = (u16)((REG_BG0CNT & 0x43) | 0x1d88);
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | 0x1e00);
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | 0x1f00);
    REG_BG1CNT = (u16)(REG_BG1CNT & ~3);
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 1);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 2);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1700;

    GXS_SetGraphicsMode(0);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubBGExtPltt(0x80);
    GX_SetBankForSubOBJ(8);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x100010;
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & 0x43) | 0x1f00);
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | 0x1e00);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | 0x1d00);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & 0x43) | 0x1c00);
    REG_DB_BG2CNT = (u16)(REG_DB_BG2CNT & ~3);
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & ~3) | 1);
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & ~3) | 2);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & ~3) | 3);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
}
