#include "libs/nitro/os/os_valarm_internal.h"

void OSi_AppendVAlarm(OSVAlarm *alarm)
{
    OSVAlarm *prev = OSi_VAlarmState.tail;

    alarm->prev = prev;
    alarm->next = 0;
    OSi_VAlarmState.tail = alarm;

    if (prev) {
        prev->next = alarm;
    } else {
        OSi_VAlarmState.head = alarm;
        OSi_SetNextVAlarm(alarm);
    }
}