#include "libs/nns/snd/fader_internal.h"

int NNSi_SndFaderGet(const NNSSndFader *fader)
{
    s64 value;

    if (fader->counter >= fader->frame) {
        return fader->target;
    }

    value = (fader->target - fader->origin) * fader->counter / fader->frame
          + fader->origin;
    return (int)value;
}