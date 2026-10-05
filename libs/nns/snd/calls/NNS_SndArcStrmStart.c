#include "libs/nns/snd/sndarc_stream_internal.h"

BOOL NNS_SndArcStrmStart(
    NNSSndStrmHandle *handle,
    int streamNo,
    u32 offset)
{
    BOOL result;

    result = NNS_SndArcStrmPrepare(handle, streamNo, offset);
    if (!result) {
        return FALSE;
    }

    NNS_SndArcStrmStartPrepared(handle);
    return TRUE;
}
