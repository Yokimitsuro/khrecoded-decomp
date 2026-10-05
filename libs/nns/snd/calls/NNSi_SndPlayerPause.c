#include "nnsys/snd.h"

extern void SND_PauseSeq(int playerNo, BOOL pause);

void NNSi_SndPlayerPause(NNSSndSeqPlayer *sequencePlayer, BOOL pause)
{
    if (sequencePlayer == NULL) {
        return;
    }

    if (pause != sequencePlayer->pauseFlag) {
        SND_PauseSeq(sequencePlayer->playerNo, pause);
        sequencePlayer->pauseFlag = (u8)pause;
    }
}
