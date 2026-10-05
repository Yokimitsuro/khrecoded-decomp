#include "nnsys/snd.h"

#define SND_DEFAULT_VARIABLE -1

extern s16 SND_GetPlayerLocalVariable(int playerNo, int variableNo);

BOOL NNS_SndPlayerReadVariable(NNSSndHandle *handle, int variableNo, s16 *value)
{
    NNSSndSeqPlayer *sequencePlayer;

    if (!NNS_SndHandleIsValid(handle)) {
        return FALSE;
    }

    sequencePlayer = handle->player;
    if (!sequencePlayer->startFlag) {
        *value = SND_DEFAULT_VARIABLE;
        return TRUE;
    }

    *value = SND_GetPlayerLocalVariable(sequencePlayer->playerNo, variableNo);
    return TRUE;
}
