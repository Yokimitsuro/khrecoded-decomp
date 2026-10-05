#include "nitro/types.h"

extern u32 data_ov001_020a0480;

void ClearSessionFlagsWord(void)
{
    *(s16 *)(data_ov001_020a0480 + 0x20e) = ~2;
}
