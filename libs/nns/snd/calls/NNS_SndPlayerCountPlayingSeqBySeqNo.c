#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);

int NNS_SndPlayerCountPlayingSeqBySeqNo(int sequenceNo)
{
    int count = 0;
    NNSSndSeqPlayer *sequencePlayer = NULL;

    while ((sequencePlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(
                &sSndSeqPlayerList, sequencePlayer)) != NULL) {
        if (sequencePlayer->seqType == NNS_SND_PLAYER_SEQ_TYPE_SEQ &&
            sequencePlayer->seqNo == sequenceNo) {
            count++;
        }
    }

    return count;
}
