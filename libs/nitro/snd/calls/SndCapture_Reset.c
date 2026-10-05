#include "libs/nns/snd/snd_internal.h"

void SndCapture_Reset(void)
{
    sSndResourceLocks.channel = 0;
    sSndResourceLocks.capture = 0;
    sSndResourceLocks.alarm = 0;
}
