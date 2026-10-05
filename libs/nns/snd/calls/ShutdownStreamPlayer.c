#include "libs/nns/snd/sndarc_stream_internal.h"

void ShutdownStreamPlayer(NNSSndStrmPlayer *player)
{
    if (!player->activeFlag) {
        return;
    }

    FreeChannel(player);
    player->closeStream(player);
    RemoveCommandByPlayer(&sStreamCommandList, player);

    if (sSoundArcStreamState.prepareThread != NULL) {
        RemoveCommandByPlayer(
            &sSoundArcStreamState.prepareThread->commandList,
            player);
    }

    FreePlayer(player);
}
