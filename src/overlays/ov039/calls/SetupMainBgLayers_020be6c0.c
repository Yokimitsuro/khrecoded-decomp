#include "nitro/types.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0_2d3d);
extern void *G2_GetBG1CharPtr(void);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);

static inline void SetBgControl(vu16 *reg, int screenBase, int charBase, int extPltt)
{
    *reg = (u16)((*reg & 0x43) | (screenBase << 8) | (charBase << 2) | extPltt);
}

void SetupMainBgLayers_020be6c0(void)
{
    GX_SetGraphicsMode(1, 0, 1);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    SetBgControl(&REG_BG1CNT, 0x1d, 2, 0);
    SetBgControl(&REG_BG2CNT, 0x1e, 2, 0);
    SetBgControl(&REG_BG3CNT, 0x1f, 0, 0);
    REG_BG0CNT = (u16)(REG_BG0CNT & ~3);
    REG_BG1CNT = (u16)((REG_BG1CNT & ~3) | 1);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 2);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0x20);
}


