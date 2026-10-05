#include "nitro/types.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ac8];
    u32 slotCount : 7;
    u32 configNibble : 4;
    u32 unk_1AC8_b11 : 21;
    u32 unk_1ACC_b0 : 6;
    u32 configField : 7;
    u32 unk_1ACC_b13 : 19;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);

u32 GetContextSlotCount(void)
{
    return func_ov002_02066fe0()->slotCount;
}
