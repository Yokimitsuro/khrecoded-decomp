#include "libs/nns/snd/sndarc_player_internal.h"

BOOL NNS_SndArcPlayerStartSeqArc(
    NNSSndHandle *handle,
    int seqArcNo,
    int index)
{
    const NNSSndArcSeqArcInfo *info;
    const NNSSndSeqArcSeqInfo *sequence;
    const NNSSndSeqArc *seqArc;

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
        sequence->param.playerNo,
        sequence->param.bankNo,
        sequence->param.playerPrio,
        sequence,
        seqArc,
        seqArcNo,
        index);
}
