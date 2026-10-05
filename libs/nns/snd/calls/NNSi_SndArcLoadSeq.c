#include "libs/nns/snd/sndarc_loader_internal.h"

NNSSndArcLoadResult NNSi_SndArcLoadSeq(
    int seqNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    NNSSndSeqData **data)
{
    const NNSSndArcSeqInfo *seqInfo;
    NNSSndSeqData *seqData = NULL;
    SNDBankData *bank = NULL;
    NNSSndArcLoadResult result;

    seqInfo = NNS_SndArcGetSeqInfo(seqNo);
    if (seqInfo == NULL) {
        return NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO;
    }

    result = NNSi_SndArcLoadBank(
        seqInfo->parameter.bankNo,
        loadFlag,
        heap,
        setAddress,
        NULL);
    if (result != NNS_SND_ARC_LOAD_SUCCESS) {
        return result;
    }

    if (loadFlag & NNS_SND_ARC_LOAD_SEQ) {
        seqData = LoadSeq(seqInfo->fileId, heap, setAddress);
        if (seqData == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ;
        }
    } else {
        seqData = NNS_SndArcGetFileAddress(seqInfo->fileId);
    }

    if (data != NULL) {
        *data = seqData;
    }

    return NNS_SND_ARC_LOAD_SUCCESS;
}
