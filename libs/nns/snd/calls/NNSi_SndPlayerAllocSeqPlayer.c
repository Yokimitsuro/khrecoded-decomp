#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_SndHandleReleaseSeq(NNSSndHandle *handle);
extern void ForceStopSeq(NNSSndSeqPlayer *sequencePlayer);
extern NNSSndSeqPlayer *AllocSeqPlayer(int priority);
extern void InsertPlayerList(NNSSndPlayer *player, NNSSndSeqPlayer *sequencePlayer);

NNSSndSeqPlayer *NNSi_SndPlayerAllocSeqPlayer(
    NNSSndHandle *handle,
    int playerNo,
    int priority)
{
    NNSSndSeqPlayer *sequencePlayer;
    NNSSndPlayer *player = &sSndPlayers[playerNo];

    if (NNS_SndHandleIsValid(handle)) {
        NNS_SndHandleReleaseSeq(handle);
    }

    if (player->playerList.numObjects >= player->playableSeqCount) {
        sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
            &player->playerList, NULL);
        if (sequencePlayer == NULL) {
            return NULL;
        }
        if (priority < sequencePlayer->priority) {
            return NULL;
        }
        ForceStopSeq(sequencePlayer);
    }

    sequencePlayer = AllocSeqPlayer(priority);
    if (sequencePlayer == NULL) {
        return NULL;
    }

    InsertPlayerList(player, sequencePlayer);
    sequencePlayer->handle = handle;
    handle->player = sequencePlayer;
    return sequencePlayer;
}
