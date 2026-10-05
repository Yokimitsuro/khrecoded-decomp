#include "libs/nns/snd/sndarc_loader_internal.h"

void DisposeCallback(void *memory, NNSSndArc *arc, u32 fileId)
{
    NNSSndArc *previousArc;
    OSIntrMode interruptState;

    if (arc == NULL) {
        return;
    }

    interruptState = OS_DisableInterrupts();
    previousArc = SND_SetActiveSlotSwap(arc);

    if (memory == NNS_SndArcGetFileAddress(fileId)) {
        NNS_SndArcSetFileAddress(fileId, NULL);
    }

    (void)SND_SetActiveSlotSwap(previousArc);
    (void)OS_RestoreInterrupts(interruptState);
}
