#include "libs/nns/snd/sndarc_stream_internal.h"

void StrmThread(void *argument)
{
    NNSSndStrmThread *thread = argument;
    NNSSndStrmCommand *command;

    while (TRUE) {
        OS_SleepThread(&thread->threadQueue);

        while (TRUE) {
            OS_LockMutex(thread->mutex);

            command = (NNSSndStrmCommand *)ReadCommandBuffer(
                &thread->commandList);
            if (command == NULL) {
                OS_UnlockMutex(thread->mutex);
                break;
            }

            NNSi_SndArcStrm_MakeWaveData(command);
            FreeCommandBuffer(command);
            OS_UnlockMutex(thread->mutex);
        }
    }
}
