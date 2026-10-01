#include "libs/nitro/os/os_alarm_internal.h"

void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire)
{
    OSAlarm *prev;
    OSAlarm *next;

    if (alarm->period > 0) {
        OSTick tick = OS_GetTick();

        fire = alarm->start;
        if (alarm->start < tick) {
            fire += alarm->period * ((tick - alarm->start) / alarm->period + 1);
        }
    }

    alarm->fire = fire;

    for (next = OSi_AlarmState.head; next; next = next->next) {
        if ((s64)(fire - next->fire) >= 0) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;

        if (prev) {
            prev->next = alarm;
        } else {
            OSi_AlarmState.head = alarm;
            OSi_SetTimer(alarm);
        }
        return;
    }

    alarm->next = 0;
    prev = OSi_AlarmState.tail;
    OSi_AlarmState.tail = alarm;
    alarm->prev = prev;

    if (prev) {
        prev->next = alarm;
    } else {
        OSi_AlarmState.head = OSi_AlarmState.tail = alarm;
        OSi_SetTimer(alarm);
    }
}