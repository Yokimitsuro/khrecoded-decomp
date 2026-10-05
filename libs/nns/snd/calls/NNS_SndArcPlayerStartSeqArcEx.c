#include "libs/nns/snd/sndarc_player_internal.h"

BOOL NNS_SndArcPlayerStartSeqArcEx(
    NNSSndHandle *handle,
    int playerNo,
    int bankNo,
    int playerPriority,
    int seqArcNo,
    int index)
{
    const NNSSndArcSeqArcInfo *info;
    const NNSSndSeqArc *seqArc;
    const NNSSndSeqArcSeqInfo *sequence;

    info = NNS_SndArcGetSeqArcInfo(seqArcNo);
    if (info == NULL) {
        return FALSE;
    }
    seqArc = NNS_SndArcGetFileAddress(info->fileId);
    if (seqArc == NULL) {
        return FALSE;
    }
    sequence = NNSi_SndSeqArcGetSeqInfo(seqArc, index);
    if (sequence == NULL) {
        return FALSE;
    }

    return StartSeqArc(
        handle,
        playerNo >= 0 ? playerNo : sequence->param.playerNo,
        bankNo >= 0 ? bankNo : sequence->param.bankNo,
        playerPriority >= 0 ? playerPriority : sequence->param.playerPrio,
        sequence,
        seqArc,
        seqArcNo,
        index);
}
