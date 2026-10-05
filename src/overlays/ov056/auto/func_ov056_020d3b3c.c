#include "nitro/types.h"

void func_ov056_020d3b3c(void *unused, void *object, u32 value)
{
    (void)unused;
    *(u32 *)((u8 *)object + 0x100) = value;
}
