#ifndef NITRO_OS_ALARM_INTERNAL_H
#define NITRO_OS_ALARM_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct OSAlarm OSAlarm;

typedef struct OSiAlarmState {
    u16 useAlarm;
    u16 padding;
    OSAlarm *head;
    OSAlarm *tail;
} OSiAlarmState;

extern OSiAlarmState OSi_AlarmState;

void OS_InitAlarm(void);
void OS_EndAlarm(void);
BOOL OS_IsAlarmAvailable(void);

#endif