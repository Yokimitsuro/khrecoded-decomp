#include "libs/nitro/os/os_event_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_WakeupThread(OSThreadQueue *queue);

void OS_SignalEvent(OSEvent *event, u32 setPattern)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (setPattern) {
        event->flag |= setPattern;
        OS_WakeupThread(&event->queue);
    }

    OS_RestoreInterrupts(enabled);
}