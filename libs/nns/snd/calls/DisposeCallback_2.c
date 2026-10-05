#include "libs/nns/snd/sndarc_stream_internal.h"

void DisposeCallback_2(
    void *memory,
    u32 size,
    u32 playerAddress,
    u32 unused)
{
    NNSSndStrmPlayer *player = (NNSSndStrmPlayer *)playerAddress;

    if (memory == player->buffer) {
        OS_LockMutex(sSoundArcStreamMutex);
        if (sSoundArcStreamState.prepareThread != NULL) {
            OS_LockMutex(sSoundArcStreamState.prepareThread->mutex);
        }

        ForceStopStrm_2(player);

        player->buffer = NULL;
        player->bufferSize = 0;
        player->numChannels = 0;
        if (player->allocChannelCount > 0) {
            NNS_SndStrmFreeChannel(&player->stream);
            player->allocChannelCount = 0;
        }

        OS_UnlockMutex(sSoundArcStreamMutex);
        if (sSoundArcStreamState.prepareThread != NULL) {
            OS_UnlockMutex(sSoundArcStreamState.prepareThread->mutex);
        }
    }
}
