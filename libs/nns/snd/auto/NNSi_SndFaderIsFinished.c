#include "libs/nns/snd/fader_internal.h"

BOOL NNSi_SndFaderIsFinished(const NNSSndFader *fader)
{
    return fader->counter >= fader->frame ? 1 : 0;
}