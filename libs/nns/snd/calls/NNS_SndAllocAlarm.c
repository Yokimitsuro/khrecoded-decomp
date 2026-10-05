#include "libs/nns/snd/snd_internal.h"

int NNS_SndAllocAlarm(void)
{
    int alarmNo;
    u32 mask = 1;

    for (alarmNo = 0; alarmNo < SND_ALARM_COUNT; alarmNo++, mask <<= 1) {
        if ((sSndResourceLocks.alarm & mask) == 0) {
            sSndResourceLocks.alarm |= mask;
            return alarmNo;
        }
    }

    return -1;
}
