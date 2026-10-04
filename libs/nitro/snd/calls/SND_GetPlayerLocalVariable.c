#include "libs/nitro/snd/snd_work_internal.h"

s16 SND_GetPlayerLocalVariable(int playerNumber, int variableNumber)
{
    DC_InvalidateRange(
        (void *)&SNDi_SharedWork->player[playerNumber].variable[variableNumber],
        sizeof(SNDi_SharedWork->player[playerNumber].variable[variableNumber]));
    return SNDi_SharedWork->player[playerNumber].variable[variableNumber];
}
