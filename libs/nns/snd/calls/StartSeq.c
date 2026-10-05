#include "libs/nns/snd/sndarc_player_internal.h"

BOOL StartSeq(
    NNSSndHandle *handle,
    int playerNo,
    int bankNo,
    int playerPriority,
    const NNSSndArcSeqInfo *info,
    int seqNo)
{
    NNSSndSeqPlayer *player;
    NNSSndHeapHandle heap;
    NNSSndSeqData *sequence;
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

    result = NNSi_SndArcLoadSeq(
        seqNo,
        NNS_SND_ARC_LOAD_SEQ,
        heap,
        FALSE,
        &sequence);
    if (result != NNS_SND_ARC_LOAD_SUCCESS) {
        NNSi_SndPlayerFreeSeqPlayer(player);
        return FALSE;
    }

    NNSi_SndPlayerStartSeq(
        player,
        (u8 *)sequence + sequence->baseOffset,
        0,
        bank);

    NNS_SndPlayerSetInitialVolume(handle, info->param.volume);
    NNS_SndPlayerSetChannelPriority(handle, info->param.channelPrio);
    NNS_SndPlayerSetSeqNo(handle, seqNo);

    return TRUE;
}
