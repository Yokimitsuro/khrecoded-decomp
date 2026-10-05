#include "nitro/types.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ad0];
    u32 unk_1AD0_b0 : 24;
    u32 configFlag : 1;
    u32 unk_1AD0_b25 : 7;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);

u32 GetContextConfigFlag1ad0(void) {
    return func_ov002_02066fe0()->configFlag;
}
