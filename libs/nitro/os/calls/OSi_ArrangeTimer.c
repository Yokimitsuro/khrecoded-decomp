#include "libs/nitro/os/os_alarm_internal.h"
#include "libs/nitro/os/os_dtcm_internal.h"
#include "libs/nitro/os/os_timer_internal.h"

extern u32 OS_DisableIrqMask(u32 mask);

void OSi_ArrangeTimer(void)
{
    OSTick tick;
    OSAlarm *alarm;
    OSAlarm *next;
    OSAlarmHandler handler;

    REG_OS_TM1CNT_H = 0;
    OS_DisableIrqMask(16);
    *(volatile u32 *)HW_INTR_CHECK_BUF |= 16;

    tick = OS_GetTick();
    alarm = OSi_AlarmState.head;
    if (alarm == 0) {
        return;
    }

    if (tick < alarm->fire) {
        OSi_SetTimer(alarm);
        return;
    }

    next = alarm->next;
    OSi_AlarmState.head = next;
    if (next == 0) {
        OSi_AlarmState.tail = 0;
    } else {
        next->prev = 0;
    }

    handler = alarm->handler;
    if (alarm->period == 0) {
        alarm->handler = 0;
    }
    if (handler) {
        handler(alarm->arg);
    }
    if (alarm->period > 0) {
        alarm->handler = handler;
        OSi_InsertAlarm(alarm, 0);
    }
    if (OSi_AlarmState.head) {
        OSi_SetTimer(OSi_AlarmState.head);
    }
}