#include "nitro/types.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ac8];
    u32 slotCount : 7;
    u32 unk_1AC8_b7 : 11;
    u32 configByte : 8;
    u32 configFlag : 1;
    u32 unk_1AC8_b27 : 5;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);

u32 GetContextConfigFlag1ac8(void) {
    return func_ov002_02066fe0()->configFlag;
}
