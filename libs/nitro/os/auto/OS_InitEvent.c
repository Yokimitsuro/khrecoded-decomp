#include "libs/nitro/os/os_event_internal.h"

void OS_InitEvent(OSEvent *event)
{
    OS_InitThreadQueue(&event->queue);
    event->flag = 0;
}
