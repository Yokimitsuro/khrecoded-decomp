#include "libs/nns/snd/snd_internal.h"

int NNS_SndPlayerCountPlayingSeqByPlayerNo(int playerNo)
{
    return sSndPlayers[playerNo].playerList.numObjects;
}
