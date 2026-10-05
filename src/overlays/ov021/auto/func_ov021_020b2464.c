#include "nitro/types.h"

u32 func_ov021_020b2464(void *destination, const void *source)
{
    *(u32 *)((u8 *)destination + 0x24) = *(const u32 *)((const u8 *)source + 0x4);
    return 7;
}
