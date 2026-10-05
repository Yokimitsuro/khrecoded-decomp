#include "nnsys/snd.h"

extern void NNSi_SndFaderSet(NNSSndFader *fader, int target, int frames);
extern void ForceStopSeq(NNSSndSeqPlayer *sequencePlayer);
extern void SetPlayerPriority(NNSSndSeqPlayer *sequencePlayer, int priority);

void NNSi_SndPlayerStopSeq(NNSSndSeqPlayer *sequencePlayer, int fadeFrames)
{
    if (sequencePlayer == NULL) {
        return;
    }
    if (sequencePlayer->status == NNS_SND_SEQ_PLAYER_STATUS_STOP) {
        return;
    }

    if (fadeFrames == 0) {
        ForceStopSeq(sequencePlayer);
        return;
    }

    NNSi_SndFaderSet(&sequencePlayer->fader, 0, fadeFrames);
    SetPlayerPriority(sequencePlayer, 0);
    sequencePlayer->status = NNS_SND_SEQ_PLAYER_STATUS_FADEOUT;
}
