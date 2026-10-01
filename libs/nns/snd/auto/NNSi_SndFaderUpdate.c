#include "libs/nns/snd/fader_internal.h"

void NNSi_SndFaderUpdate(NNSSndFader *fader)
{
    if (fader->counter < fader->frame) {
        fader->counter++;
    }
}