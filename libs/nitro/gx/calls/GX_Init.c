#include "libs/nitro/gx/gx_internal.h"

#define REG16(address) (*(volatile u16 *)(address))
#define REG32(address) (*(volatile u32 *)(address))

#define reg_GX_POWCNT        REG16(0x04000304)
#define reg_GX_DISPCNT       REG32(0x04000000)
#define reg_GX_DISPSTAT      REG16(0x04000004)
#define reg_GX_MASTER_BRIGHT REG16(0x0400006c)
#define reg_G2_BG2PA         REG16(0x04000020)
#define reg_G2_BG2PD         REG16(0x04000026)
#define reg_G2_BG3PA         REG16(0x04000030)
#define reg_G2_BG3PD         REG16(0x04000036)
#define reg_G2S_DB_BG2PA     REG16(0x04001020)
#define reg_G2S_DB_BG2PD     REG16(0x04001026)
#define reg_G2S_DB_BG3PA     REG16(0x04001030)
#define reg_G2S_DB_BG3PD     REG16(0x04001036)
#define BG_MATRIX_ONE         (1 << 8)

extern void GX_InitGXState(void);
extern s32 OS_GetLockID(void);
extern void OS_Terminate(void);
extern void MIi_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size, BOOL enable);
extern void MIi_CpuClear32(u32 data, void *dest, u32 size);

static inline void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size)
{
    MIi_DmaFill32(dmaNo, dest, data, size, 1);
}

static inline void MI_CpuFill32(void *dest, u32 data, u32 size)
{
    MIi_CpuClear32(data, dest, size);
}

void GX_Init(void)
{
    s32 lockId;

    reg_GX_POWCNT |= 0x8000;
    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~0x20e) | 0x20e);
    reg_GX_POWCNT = (u16)(reg_GX_POWCNT | 1);

    GX_InitGXState();

    while (gGXBssState.vramLockId == 0) {
        lockId = OS_GetLockID();
        if (lockId == -3) {
            OS_Terminate();
        }
        gGXBssState.vramLockId = (u16)lockId;
    }

    reg_GX_DISPSTAT = 0;
    reg_GX_DISPCNT = 0;

    if (gGXDataState.dmaId != (u32)-1) {
        MI_DmaFill32(gGXDataState.dmaId, (void *)0x04000008, 0, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        MI_DmaFill32(gGXDataState.dmaId, (void *)0x04001000, 0, 0x70);
    } else {
        MI_CpuFill32((void *)0x04000008, 0, 0x60);
        reg_GX_MASTER_BRIGHT = 0;
        MI_CpuFill32((void *)0x04001000, 0, 0x70);
    }

    reg_G2_BG2PA = BG_MATRIX_ONE;
    reg_G2_BG2PD = BG_MATRIX_ONE;
    reg_G2_BG3PA = BG_MATRIX_ONE;
    reg_G2_BG3PD = BG_MATRIX_ONE;
    reg_G2S_DB_BG2PA = BG_MATRIX_ONE;
    reg_G2S_DB_BG2PD = BG_MATRIX_ONE;
    reg_G2S_DB_BG3PA = BG_MATRIX_ONE;
    reg_G2S_DB_BG3PD = BG_MATRIX_ONE;
}