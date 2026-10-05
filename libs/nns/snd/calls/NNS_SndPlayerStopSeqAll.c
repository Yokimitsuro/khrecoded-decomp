#include "libs/nns/snd/snd_internal.h"

extern void NNSi_SndPlayerStopSeq(NNSSndSeqPlayer *sequencePlayer, int fadeFrames);

void NNS_SndPlayerStopSeqAll(int fadeFrames)
{
    NNSSndSeqPlayer *sequencePlayer;
    int i;

    for (i = 0; i < NNS_SND_PLAYER_COUNT; i++) {
        sequencePlayer = &sSndSeqPlayers[i];
        if (sequencePlayer->status != NNS_SND_SEQ_PLAYER_STATUS_STOP) {
            NNSi_SndPlayerStopSeq(sequencePlayer, fadeFrames);
        }
    }
}
