#include "libs/nns/snd/sndarc_stream_internal.h"

void FreeCommandBuffer(NNSSndStrmCommand *command)
{
    u32 interruptState;

    interruptState = OS_DisableInterrupts();
    NNS_FndAppendListObject(&sFreeStreamCommandList, command);
    OS_RestoreInterrupts(interruptState);
}
