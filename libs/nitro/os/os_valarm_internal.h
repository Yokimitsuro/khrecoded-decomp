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

typedef struct OSiVAlarmState {
    u16 enabled;
    u16 padding;
    s32 previousVCount;
    s32 frameCount;
    OSVAlarm *head;
    OSVAlarm *tail;
} OSiVAlarmState;

extern OSiVAlarmState OSi_VAlarmState;

void OSi_InsertVAlarm(OSVAlarm *alarm);
void OSi_AppendVAlarm(OSVAlarm *alarm);
void OSi_SetNextVAlarm(OSVAlarm *alarm);
void OSi_DetachVAlarm(OSVAlarm *alarm);
int OSi_CompareVCount(OSVAlarm *alarm, s32 currentVFrame, s32 currentVCount);
void OSi_VAlarmHandler(void *arg);
s32 OSi_GetVFrame(s32 vcount);

void OS_CreateVAlarm(OSVAlarm *alarm);
void OS_SetVAlarm(OSVAlarm *alarm, s16 count, s16 delay,
                  OSVAlarmHandler handler, void *arg);

#endif
