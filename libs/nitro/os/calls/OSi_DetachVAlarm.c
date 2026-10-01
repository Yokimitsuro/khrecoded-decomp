#include "libs/nitro/os/os_valarm_internal.h"

void OSi_DetachVAlarm(OSVAlarm *alarm)
{
    OSVAlarm *prev;
    OSVAlarm *next;

    if (!alarm) {
        return;
    }

    prev = alarm->prev;
    next = alarm->next;

    if (next) {
        next->prev = prev;
    } else {
        OSi_VAlarmState.tail = prev;
    }

    if (prev) {
        prev->next = next;
    } else {
        OSi_VAlarmState.head = next;
    }
}