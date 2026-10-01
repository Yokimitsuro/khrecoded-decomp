#include "libs/nitro/os/os_alarm_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode enabled);
extern void OS_Terminate(void);

void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg)
{
    OSIntrMode enabled;

    if (!alarm || alarm->handler) {
        OS_Terminate();
    }

    enabled = OS_DisableInterrupts();
    alarm->period = 0;
    alarm->handler = handler;
    alarm->arg = arg;
    OSi_InsertAlarm(alarm, OS_GetTick() + tick);
    OS_RestoreInterrupts(enabled);
}