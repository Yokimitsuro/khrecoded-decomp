#include "nitro/types.h"

extern u8 *data_0206084c;

int GetCachedSoundParam(void)
{
    return (int)*(s16 *)(data_0206084c + 0xb472a);
}
