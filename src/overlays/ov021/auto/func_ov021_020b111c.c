#include "nitro/types.h"

u32 func_ov021_020b111c(void *object)
{
    u8 *bytes = object;
    *(u16 *)(bytes + 0x2c) = 0x10;
    *(u32 *)(bytes + 0x30) = *(const u32 *)(bytes + 0x3c);
    return 0;
}
