#include "libs/nitro/os/os_valarm_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

s32 OSi_GetVFrame(s32 vcount)
{
    OSIntrMode enabled = OS_DisableInterrupts();

    if (vcount < OSi_VAlarmState.previousVCount) {
        ++OSi_VAlarmState.frameCount;
    }
    OSi_VAlarmState.previousVCount = vcount;

    OS_RestoreInterrupts(enabled);
    return OSi_VAlarmState.frameCount;
}