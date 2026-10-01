#include "libs/nitro/os/os_event_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);

u32 OS_WaitEventEx(OSEvent *event, u32 pattern, OSEventMode mode, u32 clearBit)
{
    u32 result = 0;
    OSIntrMode enabled = OS_DisableInterrupts();

    switch (mode) {
    case OS_EVENT_MODE_AND:
        while ((event->flag & pattern) != pattern) {
            OS_SleepThread(&event->queue);
        }
        result = event->flag;
        break;

    case OS_EVENT_MODE_OR:
        while ((event->flag & pattern) == 0) {
            OS_SleepThread(&event->queue);
        }
        result = event->flag;
        break;
    }

    if (result != 0) {
        event->flag &= ~clearBit;
    }

    OS_RestoreInterrupts(enabled);
    return result;
}
