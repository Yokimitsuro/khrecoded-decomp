#include "libs/nitro/snd/snd_work_internal.h"

void SNDi_InitSharedWork(SNDSharedWork *work)
{
    int playerNumber;
    int variableNumber;

    work->playerStatus = 0;
    work->channelStatus = 0;
    work->captureStatus = 0;
    work->finishCommandTag = 0;

    for (playerNumber = 0; playerNumber < SND_PLAYER_COUNT; ++playerNumber) {
        work->player[playerNumber].tickCounter = 0;
        for (variableNumber = 0; variableNumber < SND_PLAYER_VARIABLE_COUNT; ++variableNumber) {
            work->player[playerNumber].variable[variableNumber] = -1;
        }
    }
    for (variableNumber = 0; variableNumber < SND_GLOBAL_VARIABLE_COUNT; ++variableNumber) {
        work->globalVariable[variableNumber] = -1;
    }

    DC_FlushRange(work, sizeof(SNDSharedWork));
}
