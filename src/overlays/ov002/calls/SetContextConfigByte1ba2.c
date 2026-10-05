#include "nitro/types.h"

extern u32 func_ov002_02066fe0(void);

void SetContextConfigByte1ba2(s32 value) {
    u32 base = func_ov002_02066fe0();
    if (99 < value) {
        value = 99;
    }
    *(s8 *)(base + 0x1ba2) = (s8)value;
}
