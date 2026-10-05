#include "libs/nns/snd/sndarc_loader_internal.h"

NNSSndArcLoadResult NNSi_SndArcLoadBank(
    int bankNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    SNDBankData **data)
{
    const NNSSndArcBankInfo *bankInfo;
    const NNSSndArcWaveArcInfo *waveArcInfo;
    SNDBankData *bank = NULL;
    SNDWaveArc *waveArc;
    NNSSndArcLoadResult result;
    int index;

    bankInfo = NNS_SndArcGetBankInfo(bankNo);
    if (bankInfo == NULL) {
        return NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO;
    }

    if (loadFlag & NNS_SND_ARC_LOAD_BANK) {
        bank = LoadBank(bankInfo->fileId, heap, setAddress);
        if (bank == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK;
        }
    } else {
        bank = NNS_SndArcGetFileAddress(bankInfo->fileId);
    }

    for (index = 0; index < NNS_SND_ARC_BANK_TO_WAVEARC_COUNT; index++) {
        if (bankInfo->waveArcNo[index] == NNS_SND_ARC_INVALID_WAVEARC_NO) {
            continue;
        }

        waveArcInfo = NNS_SndArcGetWaveArcInfo(bankInfo->waveArcNo[index]);
        if (waveArcInfo == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;
        }

        result = NNSi_SndArcLoadWaveArc(
            bankInfo->waveArcNo[index],
            loadFlag,
            heap,
            setAddress,
            &waveArc);
        if (result != NNS_SND_ARC_LOAD_SUCCESS) {
            return result;
        }

        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {
            if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
                if (!LoadSingleWaves(
                    waveArc,
                    bank,
                    index,
                    waveArcInfo->fileId,
                    heap)) {
                    return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
                }
            }
        }

        if (bank != NULL && waveArc != NULL) {
            SND_AssignWaveArc(bank, index, waveArc);
        }
    }

    if (data != NULL) {
        *data = bank;
    }
    return NNS_SND_ARC_LOAD_SUCCESS;
}
