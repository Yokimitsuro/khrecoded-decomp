#include "libs/nns/snd/sndarc_player_internal.h"

BOOL StartSeqArc(
    NNSSndHandle *handle,
    int playerNo,
    int bankNo,
    int playerPriority,
    const NNSSndSeqArcSeqInfo *sequence,
    const NNSSndSeqArc *seqArc,
    int seqArcNo,
    int index)
{
    NNSSndSeqPlayer *player;
    NNSSndHeapHandle heap;
    SNDBankData *bank;
    NNSSndArcLoadResult result;

    player = NNSi_SndPlayerAllocSeqPlayer(
        handle,
        playerNo,
        playerPriority);
    if (player == NULL) {
        return FALSE;
    }

    heap = NNSi_SndPlayerAllocHeap(playerNo, player);

    result = NNSi_SndArcLoadBank(
        bankNo,
        NNS_SND_ARC_LOAD_BANK | NNS_SND_ARC_LOAD_WAVE,
        heap,
        FALSE,
        &bank);
    if (result != NNS_SND_ARC_LOAD_SUCCESS) {
        NNSi_SndPlayerFreeSeqPlayer(player);
        return FALSE;
    }

    NNSi_SndPlayerStartSeq(
        player,
        (u8 *)seqArc + seqArc->baseOffset,
        sequence->offset,
        bank);

    NNS_SndPlayerSetInitialVolume(handle, sequence->param.volume);
    NNS_SndPlayerSetChannelPriority(handle, sequence->param.channelPrio);
    NNS_SndPlayerSetSeqArcNo(handle, seqArcNo, index);

    return TRUE;
}
