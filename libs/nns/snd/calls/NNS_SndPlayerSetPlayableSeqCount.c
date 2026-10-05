#include "libs/nns/snd/snd_internal.h"

void NNS_SndPlayerSetPlayableSeqCount(int playerNo, int sequenceCount)
{
    sSndPlayers[playerNo].playableSeqCount = (u16)sequenceCount;
}
