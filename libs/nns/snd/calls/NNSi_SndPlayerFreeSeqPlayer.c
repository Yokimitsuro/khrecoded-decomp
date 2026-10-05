#include "libs/nns/snd/sndarc_player_internal.h"

extern void ShutdownPlayer(NNSSndSeqPlayer *player);

void NNSi_SndPlayerFreeSeqPlayer(NNSSndSeqPlayer *player)
{
    ShutdownPlayer(player);
}
