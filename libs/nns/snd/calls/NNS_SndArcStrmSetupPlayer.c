#include "libs/nns/snd/sndarc_stream_internal.h"

BOOL NNS_SndArcStrmSetupPlayer(NNSSndHeapHandle heap)
{
    int playerNo;
    const NNSSndArcStrmPlayerInfo *playerInfo;
    NNSSndStrmPlayer *player;
    void *buffer;
    u32 bufferSize;
    int i;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; ++playerNo) {
        player = &sStrmPlayers[playerNo];

        playerInfo = NNS_SndArcGetStrmPlayerInfo(playerNo);
        if (playerInfo == NULL) {
            continue;
        }

        player->numChannels = playerInfo->numChannels;
        for (i = 0; i < playerInfo->numChannels; i++) {
            player->channelNumbers[i] = playerInfo->channelNumbers[i];
        }

        if (heap != NNS_SND_HEAP_INVALID_HANDLE) {
            bufferSize = NNS_SND_STRM_BLOCK_SIZE *
                         NNS_SND_STRM_BLOCK_NUM * player->numChannels;
            buffer = NNS_SndHeapAlloc(
                heap,
                bufferSize,
                DisposeCallback_2,
                (u32)player,
                0);
            if (buffer == NULL) {
                return FALSE;
            }

            ForceStopStrm_2(player);

            player->buffer = buffer;
            player->bufferSize = bufferSize;
        }
    }

    return TRUE;
}
