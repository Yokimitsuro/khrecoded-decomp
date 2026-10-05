#include "libs/nns/snd/sndarc_stream_internal.h"

NNSSndStrmCommand *AllocCommandBuffer(void)
{
    u32 interruptState;
    NNSSndStrmCommand *command;

    interruptState = OS_DisableInterrupts();

    command = NNS_FndGetNextListObject(&sFreeStreamCommandList, NULL);
    if (command != NULL) {
        NNS_FndRemoveListObject(&sFreeStreamCommandList, command);
    }

    OS_RestoreInterrupts(interruptState);
    return command;
}
