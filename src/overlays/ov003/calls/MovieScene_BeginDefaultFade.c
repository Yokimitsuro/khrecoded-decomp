#include "nitro/types.h"

extern void func_ov003_02063fa8(u8 mode, s32 target);

int MovieScene_BeginDefaultFade(void)
{
    func_ov003_02063fa8(0, 0);
    return 6;
}

