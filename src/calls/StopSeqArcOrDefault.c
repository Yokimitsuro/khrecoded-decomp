#include "nitro/types.h"

extern u8 *gSoundWork;
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int seqArcNo);

void StopSeqArcOrDefault(int seqArcNo)
{
    if (seqArcNo == 0) {
        seqArcNo = *(int *)(gSoundWork + 0xa4);
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(seqArcNo);
}
