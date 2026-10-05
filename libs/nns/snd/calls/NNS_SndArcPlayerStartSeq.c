#include "libs/nns/snd/sndarc_player_internal.h"

BOOL NNS_SndArcPlayerStartSeq(NNSSndHandle *handle, int seqNo)
{
    const NNSSndArcSeqInfo *info;

    info = NNS_SndArcGetSeqInfo(seqNo);
    if (info == NULL) {
        return FALSE;
    }

    return StartSeq(
        handle,
        info->param.playerNo,
        info->param.bankNo,
        info->param.playerPrio,
        info,
        seqNo);
}
