#include "libs/nitro/os/os_tick_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode enabled);

OSTick OS_GetTick(void)
{
    volatile u16 countL;
    volatile OSTick countH;
    OSIntrMode enabled = OS_DisableInterrupts();

    countL = REG_OS_TM0CNT_L;
    countH = OSi_TickState.tickCounter & 0xffffffffffffULL;

    if ((REG_OS_IF & 8) && !(countL & 0x8000)) {
        countH++;
    }

    OS_RestoreInterrupts(enabled);
    return (countH << 16) | countL;
}