#include "libs/nitro/os/os_tick_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern void OS_SetIrqFunction(u32 mask, void (*function)(void));
extern u32 OS_EnableIrqMask(u32 mask);

void OS_InitTick(void)
{
    if (!OSi_TickState.useTick) {
        OSi_TickState.useTick = 1;
        OSi_SetTimerReserved(0);
        OSi_TickState.tickCounter = 0;
        REG_OS_TM0CNT_H = 0;
        REG_OS_TM0CNT_L = 0;
        REG_OS_TM0CNT_H = 0xc1;
        OS_SetIrqFunction(8, OSi_CountUpTick);
        OS_EnableIrqMask(8);
        OSi_TickState.needResetTimer = 0;
    }
}