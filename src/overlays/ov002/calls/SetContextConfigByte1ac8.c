#include "nitro/types.h"

extern u32 func_ov002_02066fe0(void);

void SetContextConfigByte1ac8(u32 value) {
    u32 base = func_ov002_02066fe0();
    *(u32 *)(base + 0x1ac8) = (*(u32 *)(base + 0x1ac8) & 0xfc03ffff) | ((value & 0xff) << 0x12);
}
