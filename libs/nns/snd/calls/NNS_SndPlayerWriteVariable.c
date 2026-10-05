#include "nnsys/snd.h"

extern void func_0200ea60(int playerNo, int variableNo, s16 value);

BOOL NNS_SndPlayerWriteVariable(NNSSndHandle *handle, int variableNo, s16 value)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return FALSE;
    }

    func_0200ea60(handle->player->playerNo, variableNo, value);
    return TRUE;
}
