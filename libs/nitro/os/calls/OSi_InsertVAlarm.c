#include "libs/nitro/os/os_valarm_internal.h"

void OSi_InsertVAlarm(OSVAlarm *alarm)
{
    OSVAlarm *prev;
    OSVAlarm *next;

    for (next = OSi_VAlarmState.head; next; next = next->next) {
        if (next->frame < alarm->frame ||
            (next->frame == alarm->frame && next->fire <= alarm->fire)) {
            continue;
        }

        prev = next->prev;
        alarm->prev = prev;
        alarm->next = next;
        next->prev = alarm;

        if (prev) {
            prev->next = alarm;
        } else {
            OSi_VAlarmState.head = alarm;
            OSi_SetNextVAlarm(alarm);
        }
        return;
    }

    OSi_AppendVAlarm(alarm);
}