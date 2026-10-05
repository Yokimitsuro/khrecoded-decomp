#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x23ac1];
    u8 rolling : 1;
    u8 pad_23ac2[0x23acc - 0x23ac2];
    u16 lineIndex;
    u16 lineDelay;
    void *script;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern u8 data_ov004_02063c30[];

void ResetScrollTextScript(void)
{
    data_ov004_020645a0.work->script = data_ov004_02063c30;
    data_ov004_020645a0.work->lineDelay = 41;
    data_ov004_020645a0.work->lineIndex = 0;
    data_ov004_020645a0.frameCount = 0;
    data_ov004_020645a0.work->rolling = 0;
}
