#include "libs/nns/snd/snd_internal.h"

extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);

void ShutdownPlayer(NNSSndSeqPlayer *sequencePlayer)
{
    NNSSndPlayer *player;

    if (sequencePlayer->handle != NULL) {
        sequencePlayer->handle->player = NULL;
        sequencePlayer->handle = NULL;
    }

    player = sequencePlayer->player;
    NNS_FndRemoveListObject(&player->playerList, sequencePlayer);
    sequencePlayer->player = NULL;

    if (sequencePlayer->heap != NULL) {
        NNS_FndAppendListObject(&player->heapList, sequencePlayer->heap);
        sequencePlayer->heap->player = NULL;
        sequencePlayer->heap = NULL;
    }

    NNS_FndRemoveListObject(&sSndSeqPlayerList, sequencePlayer);
    NNS_FndAppendListObject(&sSndFreePlayerList, sequencePlayer);
    sequencePlayer->status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
}
