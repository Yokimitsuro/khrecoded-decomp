#include "libs/nitro/card/card_event_internal.h"

extern void CARDi_LockResource(u16 lockID, u32 target);

void CARD_LockRom(u16 lockID)
{
    CARDEventListener listener[1];

    CARDi_LockResource(lockID, 1);
    OS_InitEvent(listener->event);
    OS_CreateVAlarm(listener->valarm);
    listener->Condition = CARDi_LockBusCondition;
    listener->userdata = &lockID;
    CARDi_PeekEventListener(listener);
    OS_WaitEventEx(listener->event, 1, OS_EVENT_MODE_AND, 1);
}
