#include "libs/nitro/os/os_alarm_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode enabled);

void OS_EndAlarm(void)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (OSi_AlarmState.useAlarm) {
        OSi_UnsetTimerReserved(1);
        OSi_AlarmState.useAlarm = 0;
    }

    OS_RestoreInterrupts(enabled);
}