#include "libs/nns/snd/sndarc_stream_internal.h"

void CreateThread(NNSSndStrmThread *thread, u32 priority)
{
    OS_CreateThread(
        thread->thread,
        StrmThread,
        thread,
        thread->stack + sizeof(thread->stack),
        sizeof(thread->stack),
        priority);
    NNS_FndInitList(&thread->commandList, 0);
    OS_InitMutex(thread->mutex);
    thread->threadQueue.head = thread->threadQueue.tail = NULL;
    OS_WakeupThreadDirect(thread->thread);
}
