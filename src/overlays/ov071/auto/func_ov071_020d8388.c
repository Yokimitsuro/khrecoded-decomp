#include "nitro/types.h"

void func_ov071_020d8388(void *unused, void *object, u32 value)
{
    (void)unused;
    *(u32 *)((u8 *)object + 0x7c) = value;
}
