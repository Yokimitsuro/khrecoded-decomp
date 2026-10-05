#include "libs/nns/snd/snd_internal.h"

void NNS_SndPlayerSetAllocatableChannel(int playerNo, u32 channelMask)
{
    sSndPlayers[playerNo].allocatableChannelMask = channelMask;
}
