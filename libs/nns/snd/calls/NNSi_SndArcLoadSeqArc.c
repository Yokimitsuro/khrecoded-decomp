#include "libs/nns/snd/sndarc_loader_internal.h"

NNSSndArcLoadResult NNSi_SndArcLoadSeqArc(
    int seqArcNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    NNSSndSeqArc **data)
{
    const NNSSndArcSeqArcInfo *seqArcInfo;
    NNSSndSeqArc *seqArc = NULL;

    seqArcInfo = NNS_SndArcGetSeqArcInfo(seqArcNo);
    if (seqArcInfo == NULL) {
        return NNS_SND_ARC_LOAD_ERROR_INVALID_SEQARC_NO;
    }

    if (loadFlag & NNS_SND_ARC_LOAD_SEQARC) {
        seqArc = LoadSeqArc(seqArcInfo->fileId, heap, setAddress);
        if (seqArc == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQARC;
        }
    } else {
        seqArc = NNS_SndArcGetFileAddress(seqArcInfo->fileId);
    }

    if (data != NULL) {
        *data = seqArc;
    }

    return NNS_SND_ARC_LOAD_SUCCESS;
}
