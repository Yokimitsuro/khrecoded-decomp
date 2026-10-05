#include "nitro/types.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ad0];
    u32 unk_1AD0_b0 : 4;
    u32 tierMaskLow : 10;
    u32 tierMaskHigh : 10;
    u32 unk_1AD0_b24 : 8;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);

BOOL IsTierMaskBitSet(int level)
{
    ContextConfig *config = func_ov002_02066fe0();
    return (config->tierMaskHigh & (1 << ((level - 10) / 10))) != 0;
}
