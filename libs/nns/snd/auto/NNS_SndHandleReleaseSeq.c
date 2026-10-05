#include "nnsys/snd.h"

void NNS_SndHandleReleaseSeq(NNSSndHandle *handle)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    handle->player->handle = NULL;
    handle->player = NULL;
}
