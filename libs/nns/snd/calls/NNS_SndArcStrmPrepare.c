#include "libs/nns/snd/sndarc_stream_internal.h"

BOOL NNS_SndArcStrmPrepare(
    NNSSndStrmHandle *handle,
    int streamNo,
    u32 offset)
{
    const NNSSndArcStrmInfo *streamInfo;

    streamInfo = NNS_SndArcGetStrmInfo(streamNo);
    if (streamInfo == NULL) {
        return FALSE;
    }

    return PrepareStrm(
        handle,
        streamInfo,
        streamInfo->playerNo,
        streamInfo->playerPriority,
        streamNo,
        offset,
        NULL,
        NULL,
        NULL,
        NULL);
}
