#include "libs/nns/snd/sndarc_player_internal.h"

const NNSSndSeqArcSeqInfo *NNSi_SndSeqArcGetSeqInfo(
    const NNSSndSeqArc *seqArc,
    int index)
{
    if (index < 0) {
        return NULL;
    }
    if (index >= seqArc->count) {
        return NULL;
    }
    if (seqArc->info[index].offset == NNS_SND_SEQ_ARC_INVALID_OFFSET) {
        return NULL;
    }

    return &seqArc->info[index];
}
