#include "libs/nitro/os/os_alarm_internal.h"

typedef struct OSThread {
    unsigned char reserved[0xb0];
    OSAlarm *alarmForSleep;
} OSThread;

typedef struct OSiThreadSystem {
    void *switchCallback;
    u32 rescheduleCount;
    OSThread **currentThreadPtr;
} OSiThreadSystem;

extern OSiThreadSystem OSi_ThreadSystemState;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(void *queue);
extern void OSi_SleepAlarmCallback(void *argument);

void OS_Sleep(u32 milliseconds)
{
    OSAlarm alarm;

    OS_CreateAlarm(&alarm);
    {
        OSThread *volatile thread = *OSi_ThreadSystemState.currentThreadPtr;
        OSIntrMode state = OS_DisableInterrupts();

        thread->alarmForSleep = &alarm;
        OS_SetAlarm(&alarm, ((OSTick)33514 * milliseconds) / 64,
                    OSi_SleepAlarmCallback, (void *)&thread);
        while (thread != 0) {
            OS_SleepThread(0);
        }
        OS_RestoreInterrupts(state);
    }
}
