#include "libs/nitro/os/os_timer_internal.h"

void OSi_UnsetTimerReserved(int timerNum)
{
    OSi_TimerReserved &= (u16)~(1 << timerNum);
}