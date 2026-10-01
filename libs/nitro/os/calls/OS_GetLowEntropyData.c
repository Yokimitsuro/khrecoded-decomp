#include "libs/nitro/os/os_system_work_internal.h"
#include "libs/nitro/os/os_tick_internal.h"

#define NVRAM_CONFIG_ALIGNED_SIZE 0x74
#define REG_GX_VCOUNT (*(volatile u16 *)0x04000006)
#define REG_G3X_GXSTAT (*(volatile u32 *)0x04000600)
#define REG_PAD_KEYINPUT (*(const volatile u16 *)0x04000130)
#define HW_BUTTON_XY_BUF 0x02ffffa8

static inline s32 GX_GetVCount(void)
{
    return REG_GX_VCOUNT;
}

void OS_GetLowEntropyData(u32 buffer[8])
{
    const OSSystemWork *work = OS_SYSTEM_WORK;
    const u8 *macAddress =
        (const u8 *)((u32)work->nvramUserInfo + NVRAM_CONFIG_ALIGNED_SIZE);

    buffer[0] = (u32)((GX_GetVCount() << 16) | OS_GetTickLo());
    buffer[1] =
        (u32)(*(u16 *)(macAddress + 4) << 16) ^ (u32)OSi_TickCounter;
    buffer[2] =
        (u32)(OSi_TickCounter >> 32) ^ *(u32 *)macAddress ^ work->vblankCount;
    buffer[2] ^= REG_G3X_GXSTAT;
    buffer[3] = *(u32 *)&work->realTimeClock[0];
    buffer[4] = *(u32 *)&work->realTimeClock[4];
    buffer[5] =
        ((u32)work->micSamplingData << 16) ^ work->micLastAddress;
    buffer[6] = (u32)((*(u16 *)&work->touchPanel[0] << 16) |
                      *(u16 *)&work->touchPanel[2]);
    buffer[7] =
        (u32)((work->wmRssiPool << 16) |
              (REG_PAD_KEYINPUT | *(volatile u16 *)HW_BUTTON_XY_BUF));
}
