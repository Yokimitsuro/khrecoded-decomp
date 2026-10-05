#include "nnsys/snd.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndInsertListObject(NNSFndList *list, void *target, void *object);

void InsertPlayerList(NNSSndPlayer *player, NNSSndSeqPlayer *sequencePlayer)
{
    NNSSndSeqPlayer *next = NULL;

    while ((next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
                &player->playerList, next)) != NULL) {
        if (sequencePlayer->priority < next->priority) {
            break;
        }
    }

    NNS_FndInsertListObject(&player->playerList, next, sequencePlayer);
    sequencePlayer->player = player;
}
