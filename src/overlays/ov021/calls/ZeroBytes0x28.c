#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

void ZeroBytes0x28(void *obj)
{
    MI_CpuFill8(obj, 0, 0x28);
}
