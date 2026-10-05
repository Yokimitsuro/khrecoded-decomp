#include "nnsys/snd.h"

extern void SND_SetTrackPan(int playerNo, u16 trackMask, int pan);

void NNS_SndPlayerSetTrackPan(NNSSndHandle *handle, u16 trackMask, int pan)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    SND_SetTrackPan(handle->player->playerNo, trackMask, pan);
}
