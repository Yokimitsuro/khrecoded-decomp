#include "libs/nitro/os/os_valarm_internal.h"

int OSi_CompareVCount(OSVAlarm *alarm, s32 currentVFrame, s32 currentVCount)
{
    s32 delayVFrame = currentVFrame - (s32)alarm->frame;
    s32 delayVCount = currentVCount - (s32)alarm->fire;

    if (delayVFrame < 0 || (delayVFrame == 0 && delayVCount < 0)) {
        return 0;
    }

    if (delayVCount < 0) {
        delayVCount += 263;
    }

    return delayVCount <= alarm->delay ? 1 : 2;
}