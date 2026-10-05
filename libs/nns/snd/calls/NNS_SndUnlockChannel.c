#include "libs/nns/snd/snd_internal.h"

extern void SND_UnlockChannel(u32 channelMask, u32 flags);

void NNS_SndUnlockChannel(u32 channelMask)
{
    if (channelMask == 0) {
        return;
    }

    SND_UnlockChannel(channelMask, 0);
    sSndResourceLocks.channel &= ~channelMask;
}
