#include "nitro/types.h"

void func_ov093_020c3bc4(void *object, u32 mask)
{
    *(u32 *)((u8 *)object + 4) &= ~mask;
}
