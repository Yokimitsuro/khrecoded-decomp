#include "libs/nitro/os/os_mutex_internal.h"

void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex)
{
    OSMutex *tail = thread->mutexQueue.tail;

    if (tail == 0) {
        thread->mutexQueue.head = mutex;
    } else {
        tail->link.next = mutex;
    }
    mutex->link.prev = tail;
    mutex->link.next = 0;
    thread->mutexQueue.tail = mutex;
}
