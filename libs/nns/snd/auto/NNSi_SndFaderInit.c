#include "libs/nns/snd/fader_internal.h"

void NNSi_SndFaderInit(NNSSndFader *fader)
{
    fader->origin = fader->target = 0;
    fader->counter = fader->frame = 0;
}