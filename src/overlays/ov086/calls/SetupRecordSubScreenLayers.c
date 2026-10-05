#include "nitro/types.h"

#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)
#define REG_BG0CNT_SUB (*(vu16 *)0x04001008)
#define REG_BG1CNT_SUB (*(vu16 *)0x0400100a)
#define REG_BG2CNT_SUB (*(vu16 *)0x0400100c)
#define REG_BG3CNT_SUB (*(vu16 *)0x0400100e)
#define REG_WIN0H_SUB (*(vu16 *)0x04001040)
#define REG_WIN0V_SUB (*(vu16 *)0x04001044)
#define REG_WININ_SUB (*(vu16 *)0x04001048)
#define REG_WINOUT_SUB (*(vu16 *)0x0400104a)

extern void GXS_SetGraphicsMode(int mode);

void SetupRecordSubScreenLayers(void)
{
    GXS_SetGraphicsMode(0);
    REG_BG0CNT_SUB = (u16)((REG_BG0CNT_SUB & 0x43) | 0x1a18);
    REG_BG1CNT_SUB = (u16)((REG_BG1CNT_SUB & 0x43) | 0x9b10);
    REG_BG2CNT_SUB = (u16)((REG_BG2CNT_SUB & 0x43) | 0x9d00);
    REG_BG3CNT_SUB = (u16)((REG_BG3CNT_SUB & 0x43) | 0x1f00);
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (0x1f << 8);
    REG_WININ_SUB = (u16)((REG_WININ_SUB & ~0x3f) | 0x3f);
    REG_WINOUT_SUB = (u16)((REG_WINOUT_SUB & ~0x3f) | 0x39);
    REG_WIN0H_SUB = 0x18e8;
    REG_WIN0V_SUB = 0x1884;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0xe000) | (1 << 13);
}
