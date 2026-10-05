#include "nnsys/snd.h"

void NNS_SndPlayerSetInitialVolume(NNSSndHandle *handle, int volume)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    handle->player->initialVolume = (u8)volume;
}
