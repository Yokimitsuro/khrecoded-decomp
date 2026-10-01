#ifndef NITRO_CARD_EVENT_INTERNAL_H
#define NITRO_CARD_EVENT_INTERNAL_H

#include "libs/nitro/os/os_event_internal.h"
#include "libs/nitro/os/os_valarm_internal.h"

typedef struct CARDEventListener {
    OSEvent event[1];
    OSVAlarm valarm[1];
    BOOL (*Condition)(void *userdata);
    void *userdata;
    u16 lockID;
    u8 padding[2];
} CARDEventListener;

BOOL CARDi_LockBusCondition(void *userdata);
void CARDi_PeekEventListener(void *arg);

#endif
