#include "nnsys/snd.h"

#define SND_VOLUME_DB_MIN (-723)

extern void SND_StopSeq(int playerNo);
extern void SND_SetPlayerVolume(int playerNo, int volume);
extern void ShutdownPlayer(NNSSndSeqPlayer *sequencePlayer);

void ForceStopSeq(NNSSndSeqPlayer *sequencePlayer)
{
    if (sequencePlayer->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) {
        SND_SetPlayerVolume(sequencePlayer->playerNo, SND_VOLUME_DB_MIN);
    }
    SND_StopSeq(sequencePlayer->playerNo);
    ShutdownPlayer(sequencePlayer);
}
