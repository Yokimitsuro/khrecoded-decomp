#include "nnsys/snd.h"

extern void NNSi_SndPlayerStopSeq(NNSSndSeqPlayer *sequencePlayer, int fadeFrames);

void NNS_SndPlayerStopSeq(NNSSndHandle *handle, int fadeFrames)
{
    NNSi_SndPlayerStopSeq(handle->player, fadeFrames);
}
