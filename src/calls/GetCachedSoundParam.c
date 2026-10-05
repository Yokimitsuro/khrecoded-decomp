#include "nitro/types.h"

extern u8 *gSoundWork;

int GetCachedSoundParam(void)
{
    return (int)*(s16 *)(gSoundWork + 0xb472a);
}
