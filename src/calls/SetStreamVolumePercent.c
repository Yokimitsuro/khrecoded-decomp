#include "nitro/types.h"

extern u8 *gSoundWork;

void SetStreamVolumePercent(int percent)
{
    *(s16 *)(gSoundWork + 0xb47d6) = (s16)((percent * 0x7f) / 100);
}
