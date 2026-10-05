#include "nitro/types.h"

extern u8 *data_0206084c;

void SetStreamVolumePercent(int percent)
{
    *(s16 *)(data_0206084c + 0xb47d6) = (s16)((percent * 0x7f) / 100);
}
