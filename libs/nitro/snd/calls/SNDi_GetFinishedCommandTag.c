#include "libs/nitro/snd/snd_work_internal.h"

u32 SNDi_GetFinishedCommandTag(void)
{
    DC_InvalidateRange((void *)&SNDi_SharedWork->finishCommandTag,
                       sizeof(SNDi_SharedWork->finishCommandTag));
    return SNDi_SharedWork->finishCommandTag;
}
