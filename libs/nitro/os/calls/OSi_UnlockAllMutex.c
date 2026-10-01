#include "libs/nitro/os/os_mutex_internal.h"

extern OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutexQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);

void OSi_UnlockAllMutex(OSThread *thread)
{
    OSMutex *mutex;

    if (thread->mutexQueue.head == 0) {
        return;
    }

    do {
        mutex = OSi_RemoveMutexLinkFromQueue(&thread->mutexQueue);
        OS_SetMutexCount(mutex, 0);
        mutex->thread = 0;
        OS_SetMutexType(mutex, OS_MUTEX_TYPE_NONE);
        OS_WakeupThread(&mutex->queue);
    } while (thread->mutexQueue.head != 0);
}
