#include "libs/nitro/card/card_event_internal.h"

void CARDi_PeekEventListener(void *arg)
{
    CARDEventListener *listener = (CARDEventListener *)arg;

    if (listener->Condition(listener->userdata)) {
        OS_SignalEvent(listener->event, 1);
    } else {
        OS_SetVAlarm(listener->valarm, 192, 263, CARDi_PeekEventListener, listener);
    }
}
