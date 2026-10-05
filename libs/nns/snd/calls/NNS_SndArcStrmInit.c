#include "libs/nns/snd/sndarc_stream_internal.h"

#pragma opt_rotateloops off
#pragma opt_strength_reduction off
void NNS_SndArcStrmInit(u32 threadPriority, NNSSndHeapHandle heap)
{
    int i;
    int playerNo;
    NNSSndStrmPlayer *player;

    if (sSoundArcStreamState.initialized) {
        NNS_SndArcStrmSetupPlayer(heap);
        return;
    }
    sSoundArcStreamState.initialized = TRUE;

    NNS_FndInitList(&sFreeStreamCommandList, 0);
    for (i = 0; i < NNS_SND_STRM_COMMAND_NUM; i++) {
        NNS_FndAppendListObject(
            &sFreeStreamCommandList,
            &sStreamCommands[i]);
    }
    OS_InitMutex(sStreamCommandMutex);

    sSoundArcStreamState.decodeBuffer = sDecodeBufferArea;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; playerNo++) {
        player = &sStrmPlayers[playerNo];

        player->activeFlag = FALSE;
        FS_InitFile((FSFile *)player->fileStorage);
        NNS_SndStrmInit(&player->stream);
        player->playerNo = playerNo;
        player->numChannels = 0;
        player->buffer = NULL;
        player->bufferSize = 0;
        player->allocChannelCount = 0;
    }

    NNS_SndArcStrmSetupPlayer(heap);
    CreateThread(&sPrepareStreamThread, threadPriority);
}
#pragma opt_strength_reduction reset
#pragma opt_rotateloops reset
