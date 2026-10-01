#ifndef NITRO_OS_EVENT_INTERNAL_H
#define NITRO_OS_EVENT_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct OSEvent {
    volatile u32 flag;
    OSThreadQueue queue;
} OSEvent;

typedef enum OSEventMode {
    OS_EVENT_MODE_AND = 0,
    OS_EVENT_MODE_OR = 1
} OSEventMode;

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = 0;
}

void OS_InitEvent(OSEvent *event);
u32 OS_WaitEventEx(OSEvent *event, u32 pattern, OSEventMode mode, u32 clearBit);
void OS_SignalEvent(OSEvent *event, u32 setPattern);

#endif
