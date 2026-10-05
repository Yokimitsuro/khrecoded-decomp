#include "libs/nns/snd/snd_internal.h"

void SND_ClearChannelBit(int alarmNo)
{
    sSndResourceLocks.alarm &= ~(1 << alarmNo);
}
