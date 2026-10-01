#include "libs/nitro/os/os_tick_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

void OSi_CountUpTick(void)
{
    OSi_TickState.tickCounter++;

    if (OSi_TickState.needResetTimer) {
        REG_OS_TM0CNT_H = 0;
        REG_OS_TM0CNT_L = 0;
        REG_OS_TM0CNT_H = 0xc1;
        OSi_TickState.needResetTimer = 0;
    }

    OSi_EnterTimerCallback(0, (void (*)(void *))OSi_CountUpTick, 0);
}