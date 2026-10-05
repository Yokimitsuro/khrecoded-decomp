#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndInsertListObject(NNSFndList *list, void *target, void *object);

void InsertPrioList(NNSSndSeqPlayer *sequencePlayer)
{
    NNSSndSeqPlayer *next = NULL;

    while ((next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
                &sSndSeqPlayerList, next)) != NULL) {
        if (sequencePlayer->priority < next->priority) {
            break;
        }
    }

    NNS_FndInsertListObject(&sSndSeqPlayerList, next, sequencePlayer);
}
