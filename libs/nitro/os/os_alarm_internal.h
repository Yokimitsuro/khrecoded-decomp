#ifndef NITRO_OS_ALARM_INTERNAL_H
#define NITRO_OS_ALARM_INTERNAL_H

#include "libs/nitro/os/os_tick_internal.h"

typedef void (*OSAlarmHandler)(void *arg);
typedef struct OSiAlarm OSAlarm;

struct OSiAlarm {
    OSAlarmHandler handler;
    void *arg;
    u32 tag;
    OSTick fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTick period;
    OSTick start;
};

typedef struct OSiAlarmState {
    u16 useAlarm;
    u16 padding;
    OSAlarm *head;
    OSAlarm *tail;
} OSiAlarmState;

extern OSiAlarmState OSi_AlarmState;

void OSi_SetTimer(OSAlarm *alarm);
void OSi_InsertAlarm(OSAlarm *alarm, OSTick fire);
void OSi_ArrangeTimer(void);
void OSi_AlarmHandler(void *arg);
void OS_InitAlarm(void);
void OS_EndAlarm(void);
BOOL OS_IsAlarmAvailable(void);
void OS_CreateAlarm(OSAlarm *alarm);
void OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);
void OS_CancelAlarm(OSAlarm *alarm);

#endif