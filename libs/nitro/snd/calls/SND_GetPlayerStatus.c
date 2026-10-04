#include "libs/nitro/snd/snd_work_internal.h"

u32 SND_GetPlayerStatus(void)
{
    DC_InvalidateRange((void *)&SNDi_SharedWork->playerStatus,
                       sizeof(SNDi_SharedWork->playerStatus));
    return SNDi_SharedWork->playerStatus;
}
