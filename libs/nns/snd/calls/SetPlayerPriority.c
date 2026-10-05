#include "libs/nns/snd/snd_internal.h"

extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void InsertPlayerList(NNSSndPlayer *player, NNSSndSeqPlayer *sequencePlayer);
extern void InsertPrioList(NNSSndSeqPlayer *sequencePlayer);

void SetPlayerPriority(NNSSndSeqPlayer *sequencePlayer, int priority)
{
    NNSSndPlayer *player = sequencePlayer->player;

    if (player != NULL) {
        NNS_FndRemoveListObject(&player->playerList, sequencePlayer);
        sequencePlayer->player = NULL;
    }

    NNS_FndRemoveListObject(&sSndSeqPlayerList, sequencePlayer);
    sequencePlayer->priority = (u8)priority;

    if (player != NULL) {
        InsertPlayerList(player, sequencePlayer);
    }
    InsertPrioList(sequencePlayer);
}
