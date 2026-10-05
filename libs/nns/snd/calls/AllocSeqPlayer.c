#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void ForceStopSeq(NNSSndSeqPlayer *sequencePlayer);
extern void InsertPrioList(NNSSndSeqPlayer *sequencePlayer);

NNSSndSeqPlayer *AllocSeqPlayer(int priority)
{
    NNSSndSeqPlayer *sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
        &sSndFreePlayerList, NULL);

    if (sequencePlayer == NULL) {
        sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
            &sSndSeqPlayerList, NULL);
        if (priority < sequencePlayer->priority) {
            return NULL;
        }
        ForceStopSeq(sequencePlayer);
    }

    NNS_FndRemoveListObject(&sSndFreePlayerList, sequencePlayer);
    sequencePlayer->priority = (u8)priority;
    InsertPrioList(sequencePlayer);
    return sequencePlayer;
}
