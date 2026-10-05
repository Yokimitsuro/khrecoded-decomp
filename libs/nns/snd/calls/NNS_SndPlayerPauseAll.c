#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNSi_SndPlayerPause(NNSSndSeqPlayer *sequencePlayer, BOOL pause);

void NNS_SndPlayerPauseAll(BOOL pause)
{
    NNSSndSeqPlayer *sequencePlayer;
    NNSSndSeqPlayer *next;

    for (sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
             &sSndSeqPlayerList, NULL);
         sequencePlayer != NULL;
         sequencePlayer = next) {
        next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
            &sSndSeqPlayerList, sequencePlayer);
        NNSi_SndPlayerPause(sequencePlayer, pause);
    }
}
