#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNSi_SndPlayerPause(NNSSndSeqPlayer *sequencePlayer, BOOL pause);

void NNS_SndPlayerPauseByPlayerNo(int playerNo, BOOL pause)
{
    NNSSndSeqPlayer *sequencePlayer;
    NNSSndSeqPlayer *next;

    for (sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
             &sSndPlayers[playerNo].playerList, NULL);
         sequencePlayer != NULL;
         sequencePlayer = next) {
        next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
            &sSndPlayers[playerNo].playerList, sequencePlayer);
        NNSi_SndPlayerPause(sequencePlayer, pause);
    }
}
