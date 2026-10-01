#include "libs/nitro/os/os_mutex_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex);
extern OSThreadInfo data_02056b6c;

BOOL OS_TryLockMutex(OSMutex *mutex)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSThread *current = data_02056b6c.current;
    BOOL locked;

    if (mutex->thread == 0) {
        OSi_SetMutexType(mutex, OS_MUTEX_TYPE_NORMAL);
        mutex->thread = current;
        OSi_SetMutexCount(mutex, mutex->count + 1);
        OSi_EnqueueTail(current, mutex);
        locked = 1;
    } else if (mutex->thread == current) {
        OSi_SetMutexCount(mutex, mutex->count + 1);
        locked = 1;
    } else {
        locked = 0;
    }

    OS_RestoreInterrupts(enabled);
    return locked;
}
