#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

void ZeroAndSetField0xd4(void *obj)
{
    MI_CpuFill8(obj, 0, 0xdc);
    *(u32 *)((u8 *)obj + 0xd4) = 1;
}
