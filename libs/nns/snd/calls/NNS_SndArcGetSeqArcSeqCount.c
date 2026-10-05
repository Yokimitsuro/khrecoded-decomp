#include "libs/nns/snd/sndarc_internal.h"

u32 NNS_SndArcGetSeqArcSeqCount(int seqArcNo)
{
    const NNSSndArcSeqArcInfo *info;
    const NNSSndSeqArc *seqArc;

    info = NNS_SndArcGetSeqArcInfo(seqArcNo);
    if (info == NULL) {
        return 0;
    }

    seqArc = NNS_SndArcGetFileAddress(info->fileId);
    if (seqArc == NULL) {
        return 0;
    }

    return NNSi_SndSeqArcGetSeqCount(seqArc);
}
