#include "libs/nitro/os/os_tick_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode enabled);

void OS_SetTick(OSTick count)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    REG_OS_IF = 8;
    OSi_TickState.needResetTimer = 1;
    OSi_TickState.tickCounter = count >> 16;
    REG_OS_TM0CNT_H = 0;
    REG_OS_TM0CNT_L = (u16)(count & 0xffff);
    REG_OS_TM0CNT_H = 0xc1;

    OS_RestoreInterrupts(enabled);
}