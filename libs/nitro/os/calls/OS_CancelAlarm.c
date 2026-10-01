#include "libs/nitro/os/os_alarm_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode enabled);

void OS_CancelAlarm(OSAlarm *alarm)
{
    OSAlarm *next;
    OSIntrMode enabled = OS_DisableInterrupts();

    if (alarm->handler == 0) {
        OS_RestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        OSi_AlarmState.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }

    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        OSi_AlarmState.head = next;
        if (next) {
            OSi_SetTimer(next);
        }
    }

    alarm->handler = 0;
    alarm->period = 0;
    OS_RestoreInterrupts(enabled);
}