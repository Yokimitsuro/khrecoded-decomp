#include "nitro/types.h"

extern u8 *data_ov003_020658c0;

BOOL MovieScene_IsFlag8b9Clear(void)
{
    return data_ov003_020658c0[0x8b9] == 0;
}

