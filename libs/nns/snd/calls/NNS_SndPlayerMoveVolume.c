#include "nnsys/snd.h"

#define FADER_SHIFT 8

extern void NNSi_SndFaderSet(NNSSndFader *fader, int target, int frames);

void NNS_SndPlayerMoveVolume(NNSSndHandle *handle, int targetVolume, int frames)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }
    if (handle->player->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) {
        return;
    }

    NNSi_SndFaderSet(&handle->player->fader, targetVolume << FADER_SHIFT, frames);
}
