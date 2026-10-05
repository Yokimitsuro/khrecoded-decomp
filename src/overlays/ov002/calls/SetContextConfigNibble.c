#include "nitro/types.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ac8];
    u32 slotCount : 7;
    u32 configNibble : 4;
    u32 unk_1AC8_b11 : 21;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);

void SetContextConfigNibble(int value)
{
    ContextConfig *config = func_ov002_02066fe0();
    config->configNibble = value;
    if (config->configNibble >= 11) {
        config->configNibble = 10;
    }
}
