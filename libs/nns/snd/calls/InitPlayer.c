#include "nnsys/snd.h"

#define FADER_SHIFT 8

extern void NNSi_SndFaderInit(NNSSndFader *fader);
extern void NNSi_SndFaderSet(NNSSndFader *fader, int target, int frames);

void InitPlayer(NNSSndSeqPlayer *sequencePlayer)
{
    sequencePlayer->pauseFlag = FALSE;
    sequencePlayer->startFlag = FALSE;
    sequencePlayer->prepareFlag = FALSE;
    sequencePlayer->seqType = NNS_SND_PLAYER_SEQ_TYPE_INVALID;
    sequencePlayer->volume = 0;
    sequencePlayer->initialVolume = 127;
    sequencePlayer->externalVolume = 127;
    NNSi_SndFaderInit(&sequencePlayer->fader);
    NNSi_SndFaderSet(&sequencePlayer->fader, 127 << FADER_SHIFT, 1);
}
