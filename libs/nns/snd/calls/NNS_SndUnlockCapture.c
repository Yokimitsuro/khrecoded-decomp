#include "libs/nns/snd/snd_internal.h"

void NNS_SndUnlockCapture(u32 captureMask)
{
    sSndResourceLocks.capture &= ~captureMask;
}
