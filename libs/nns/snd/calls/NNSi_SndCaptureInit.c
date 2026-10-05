#include "libs/nns/snd/capture_internal.h"

void NNSi_SndCaptureInit(void)
{
    sSndCaptureThreadCreated = FALSE;
    sSndCaptureState.active = FALSE;
}
