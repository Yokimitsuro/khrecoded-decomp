#include "libs/nitro/os/os_mutex_internal.h"

extern void OSi_UnlockMutexCore(OSMutex *mutex, u32 type);

void OS_UnlockMutex(OSMutex *mutex)
{
    OSi_UnlockMutexCore(mutex, OS_MUTEX_TYPE_STD);
}
