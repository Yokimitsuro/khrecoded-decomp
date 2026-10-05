#include "nitro/types.h"

void func_ov091_020c2784(void *object, u32 mask)
{
    *(u32 *)((u8 *)object + 4) &= ~mask;
}
