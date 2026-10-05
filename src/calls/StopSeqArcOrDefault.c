#include "nitro/types.h"

extern u8 *data_0206084c;
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int seqArcNo);

void StopSeqArcOrDefault(int seqArcNo)
{
    if (seqArcNo == 0) {
        seqArcNo = *(int *)(data_0206084c + 0xa4);
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(seqArcNo);
}
