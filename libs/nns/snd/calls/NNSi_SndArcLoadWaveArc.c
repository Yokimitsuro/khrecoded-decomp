#include "libs/nns/snd/sndarc_loader_internal.h"

NNSSndArcLoadResult NNSi_SndArcLoadWaveArc(
    int waveArcNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    SNDWaveArc **data)
{
    const NNSSndArcWaveArcInfo *waveArcInfo;
    SNDWaveArc *waveArc = NULL;

    waveArcInfo = NNS_SndArcGetWaveArcInfo(waveArcNo);
    if (waveArcInfo == NULL) {
        return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;
    }

    if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {
            waveArc = NNS_SndArcLoadWaveArcTable(
                waveArcInfo->fileId,
                heap,
                setAddress);
        } else {
            waveArc = LoadWaveArc(waveArcInfo->fileId, heap, setAddress);
        }
        if (waveArc == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
        }
    } else {
        waveArc = NNS_SndArcGetFileAddress(waveArcInfo->fileId);
    }

    if (data != NULL) {
        *data = waveArc;
    }
    return NNS_SND_ARC_LOAD_SUCCESS;
}
