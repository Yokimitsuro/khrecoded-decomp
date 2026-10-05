#include "libs/nns/snd/snd_internal.h"

extern void SND_LockChannel(u32 channelMask, u32 flags);

int NNS_SndLockChannel(u32 channelMask)
{
    if (channelMask == 0) {
        return TRUE;
    }
    if ((channelMask & sSndResourceLocks.channel) != 0) {
        return FALSE;
    }

    SND_LockChannel(channelMask, 0);
    sSndResourceLocks.channel |= channelMask;
    return TRUE;
}
