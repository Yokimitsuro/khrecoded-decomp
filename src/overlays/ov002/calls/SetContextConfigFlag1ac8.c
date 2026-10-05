#include "nitro/types.h"

extern u32 func_ov002_02066fe0(void);

void SetContextConfigFlag1ac8(u32 value) {
    u32 base = func_ov002_02066fe0();
    *(u32 *)(base + 0x1ac8) = (*(u32 *)(base + 0x1ac8) & 0xfbffffff) | ((value & 1) << 0x1a);
}
