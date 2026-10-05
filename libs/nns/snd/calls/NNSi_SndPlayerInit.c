#include "libs/nns/snd/snd_internal.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))
#define NNS_FND_INIT_LIST(list, type, member) NNS_FndInitList(list, offsetof(type, member))

extern void NNS_FndInitList(NNSFndList *list, u16 offset);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);

void NNSi_SndPlayerInit(void)
{
    NNSSndPlayer *player;
    int playerNo;

    NNS_FND_INIT_LIST(&sSndSeqPlayerList, NNSSndSeqPlayer, prioLink);
    NNS_FND_INIT_LIST(&sSndFreePlayerList, NNSSndSeqPlayer, prioLink);

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_COUNT; playerNo++) {
        sSndSeqPlayers[playerNo].status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
        sSndSeqPlayers[playerNo].playerNo = (u8)playerNo;
        NNS_FndAppendListObject(&sSndFreePlayerList, &sSndSeqPlayers[playerNo]);
    }

    for (playerNo = 0; playerNo < NNS_SND_LOGICAL_PLAYER_COUNT; playerNo++) {
        player = &sSndPlayers[playerNo];
        NNS_FND_INIT_LIST(&player->playerList, NNSSndSeqPlayer, playerLink);
        NNS_FND_INIT_LIST(&player->heapList, NNSSndPlayerHeap, link);
        player->volume = 127;
        player->playableSeqCount = 1;
        player->allocatableChannelMask = 0;
    }
}
