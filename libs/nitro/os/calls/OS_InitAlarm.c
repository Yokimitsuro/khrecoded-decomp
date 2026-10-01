#include "libs/nitro/os/os_alarm_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern u32 OS_DisableIrqMask(u32 mask);

void OS_InitAlarm(void)
{
    if (!OSi_AlarmState.useAlarm) {
        OSi_AlarmState.useAlarm = 1;
        OSi_SetTimerReserved(1);
        OSi_AlarmState.head = 0;
        OSi_AlarmState.tail = 0;
        OS_DisableIrqMask(16);
    }
}