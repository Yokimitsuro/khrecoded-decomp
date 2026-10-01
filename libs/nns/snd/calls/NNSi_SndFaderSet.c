#include "libs/nns/snd/fader_internal.h"

void NNSi_SndFaderSet(NNSSndFader *fader, int target, int frame)
{
    fader->origin = NNSi_SndFaderGet(fader);
    fader->target = target;
    fader->frame = frame;
    fader->counter = 0;
}