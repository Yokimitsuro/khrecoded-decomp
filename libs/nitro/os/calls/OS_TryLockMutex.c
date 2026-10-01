#include "libs/nitro/os/os_mutex_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex);

BOOL OS_TryLockMutex(OSMutex *mutex)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSThread *current = OSi_ThreadInfo.current;
    BOOL locked;

    if (mutex->thread == 0) {
        mutex->thread = current;
        OS_SetMutexType(mutex, OS_MUTEX_TYPE_STD);
        OS_IncreaseMutexCount(mutex);
        OSi_EnqueueTail(current, mutex);
        locked = 1;
    } else if (mutex->thread == current) {
        OS_IncreaseMutexCount(mutex);
        locked = 1;
    } else {
        locked = 0;
    }

    OS_RestoreInterrupts(enabled);
    return locked;
}
