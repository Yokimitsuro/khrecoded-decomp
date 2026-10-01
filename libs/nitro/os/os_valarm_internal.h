#ifndef NITRO_OS_VALARM_INTERNAL_H
#define NITRO_OS_VALARM_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef void (*OSVAlarmHandler)(void *arg);

typedef struct OSVAlarm {
    OSVAlarmHandler handler;
    void *arg;
    u32 tag;
    u32 frame;
    s16 fire;
    s16 delay;
    struct OSVAlarm *prev;
    struct OSVAlarm *next;
    BOOL period;
    BOOL finish;
    BOOL canceled;
} OSVAlarm;

void OS_CreateVAlarm(OSVAlarm *alarm);
void OS_SetVAlarm(OSVAlarm *alarm, s16 count, s16 delay,
                  OSVAlarmHandler handler, void *arg);

#endif
