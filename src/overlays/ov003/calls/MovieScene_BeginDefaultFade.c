#include "nitro/types.h"

extern void MovieScene_BeginFade(u8 mode, s32 target);

int MovieScene_BeginDefaultFade(void)
{
    MovieScene_BeginFade(0, 0);
    return 6;
}

