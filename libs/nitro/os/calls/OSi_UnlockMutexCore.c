#include "libs/nitro/os/os_mutex_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OSi_DequeueItem(OSThread *thread, OSMutex *mutex);
extern void OS_WakeupThread(OSThreadQueue *queue);

void OSi_UnlockMutexCore(OSMutex *mutex, u32 type)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    OSThread *currentThread = OS_GetCurrentThread();
    BOOL unlocked = 0;

    if (type != OS_MUTEX_TYPE_NONE && type != OS_GetMutexType(mutex)) {
        OS_RestoreInterrupts(enabled);
        return;
    }

    switch (OS_GetMutexType(mutex)) {
    case OS_MUTEX_TYPE_STD:
    case OS_MUTEX_TYPE_W:
        if (mutex->thread == currentThread) {
            OS_DecreaseMutexCount(mutex);
            if (OS_GetMutexCount(mutex) == 0) {
                unlocked = 1;
            }
        }
        break;

    case OS_MUTEX_TYPE_R:
        OS_DecreaseMutexCount(mutex);
        if (OS_GetMutexCount(mutex) == 0) {
            unlocked = 1;
        }
        break;

    default:
        OS_RestoreInterrupts(enabled);
        return;
    }

    if (unlocked) {
        OSi_DequeueItem(currentThread, mutex);
        mutex->thread = 0;
        OS_SetMutexType(mutex, OS_MUTEX_TYPE_NONE);
        OS_WakeupThread(&mutex->queue);
    }

    OS_RestoreInterrupts(enabled);
}
