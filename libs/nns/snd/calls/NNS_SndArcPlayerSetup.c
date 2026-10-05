#include "libs/nns/snd/sndarc_player_internal.h"

BOOL NNS_SndArcPlayerSetup(NNSSndHeapHandle heap)
{
    NNSSndArc *arc = NNS_SndArcGetCurrent();
    int playerNo;
    const NNSSndArcPlayerInfo *playerInfo;

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_NUM; ++playerNo) {
        playerInfo = NNS_SndArcGetPlayerInfo(playerNo);
        if (playerInfo == NULL) {
            continue;
        }

        NNS_SndPlayerSetPlayableSeqCount(playerNo, playerInfo->seqMax);
        NNS_SndPlayerSetAllocatableChannel(
            playerNo,
            playerInfo->allocChBitFlag);

        if (playerInfo->heapSize > 0 &&
            heap != NNS_SND_HEAP_INVALID_HANDLE) {
            int i;

            for (i = 0; i < playerInfo->seqMax; i++) {
                if (!NNS_SndPlayerCreateHeap(
                    playerNo,
                    heap,
                    playerInfo->heapSize)) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}
