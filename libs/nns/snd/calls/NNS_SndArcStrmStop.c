#include "libs/nns/snd/sndarc_stream_internal.h"

inline BOOL NNS_SndStrmHandleIsValid(const NNSSndStrmHandle *handle)
{
    return handle->player != NULL;
}

void NNS_SndArcStrmStop(NNSSndStrmHandle *handle, int fadeFrames)
{
    if (!NNS_SndStrmHandleIsValid(handle)) {
        return;
    }

    SNDi_FreeVoiceChannel(handle->player, fadeFrames);
}
