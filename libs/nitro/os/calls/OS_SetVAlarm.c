#include "libs/nitro/os/os_valarm_internal.h"

typedef int s32;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_Terminate(void);
extern s32 OSi_GetVFrame(s32 currentVCount);
extern void OSi_InsertVAlarm(OSVAlarm *alarm);

void OS_SetVAlarm(OSVAlarm *alarm, s16 count, s16 delay,
                  OSVAlarmHandler handler, void *arg)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    s32 currentVCount;
    s32 currentVFrame;

    if (!alarm || alarm->handler) {
        OS_Terminate();
    }

    currentVCount = *(volatile u16 *)0x04000006;
    currentVFrame = OSi_GetVFrame(currentVCount);

    alarm->period = 0;
    alarm->fire = count;
    alarm->frame = (u32)((count > currentVCount) ? currentVFrame : currentVFrame + 1);
    alarm->delay = delay;
    alarm->handler = handler;
    alarm->arg = arg;
    alarm->canceled = 0;

    OSi_InsertVAlarm(alarm);
    OS_RestoreInterrupts(enabled);
}