#include "libs/nitro/os/os_mutex_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern BOOL OS_TryLockMutex(OSMutex *mutex);
extern void OS_SleepThread(OSThreadQueue *queue);
extern OSThreadInfo data_02056b6c;

void OS_LockMutex(OSMutex *mutex)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSThread *current = data_02056b6c.current;
    OSMutex *none = 0;

    for (;;) {
        if (OS_TryLockMutex(mutex)) {
            break;
        }
        current->mutex = mutex;
        OS_SleepThread(&mutex->queue);
        current->mutex = none;
    }

    OS_RestoreInterrupts(enabled);
}
