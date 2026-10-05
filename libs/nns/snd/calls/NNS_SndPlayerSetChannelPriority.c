#include "nnsys/snd.h"

extern void SND_SetPlayerChannelPriority(int playerNo, int priority);

void NNS_SndPlayerSetChannelPriority(NNSSndHandle *handle, int priority)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    SND_SetPlayerChannelPriority(handle->player->playerNo, priority);
}
