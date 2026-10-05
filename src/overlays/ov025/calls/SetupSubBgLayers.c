#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)

extern void GXS_SetGraphicsMode(int mode);

void SetupSubBgLayers(void)
{
    GXS_SetGraphicsMode(0);
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0x0a00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0x0b04;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0x4c00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x4e04;
    REG_DB_BG0CNT = REG_DB_BG0CNT & ~3;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~3) | 1;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~3) | 2;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~3) | 3;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
}
