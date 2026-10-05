#include "nnsys/snd.h"

extern void NNSi_SndPlayerPause(NNSSndSeqPlayer *sequencePlayer, BOOL pause);

void NNS_SndPlayerPause(NNSSndHandle *handle, BOOL pause)
{
    NNSi_SndPlayerPause(handle->player, pause);
}
