#include "nnsys/snd.h"

extern void SND_PrepareSeq(
    int playerNo,
    const void *base,
    u32 offset,
    const SNDBankData *bank);
extern void SND_SetTrackAllocatableChannel(int playerNo, u32 trackMask, u32 channelMask);
extern u32 SND_GetCurrentCommandTag(void);
extern void InitPlayer(NNSSndSeqPlayer *sequencePlayer);

void NNSi_SndPlayerStartSeq(
    NNSSndSeqPlayer *sequencePlayer,
    const void *sequenceData,
    u32 sequenceOffset,
    const SNDBankData *bank)
{
    NNSSndPlayer *player = sequencePlayer->player;

    SND_PrepareSeq(sequencePlayer->playerNo, sequenceData, sequenceOffset, bank);
    if (player->allocatableChannelMask != 0) {
        SND_SetTrackAllocatableChannel(
            sequencePlayer->playerNo,
            0xffff,
            player->allocatableChannelMask);
    }

    InitPlayer(sequencePlayer);
    sequencePlayer->commandTag = SND_GetCurrentCommandTag();
    sequencePlayer->prepareFlag = TRUE;
    sequencePlayer->status = NNS_SND_SEQ_PLAYER_STATUS_PLAY;
}
