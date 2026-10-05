#include "libs/nns/snd/sndarc_stream_internal.h"

inline BOOL NNS_SndStrmHandleIsValid(const NNSSndStrmHandle *handle)
{
    return handle->player != NULL;
}

void NNS_SndArcStrmStartPrepared(NNSSndStrmHandle *handle)
{
    if (!NNS_SndStrmHandleIsValid(handle)) {
        return;
    }

    handle->player->startFlag = TRUE;
}
