#include "nitro/types.h"

extern void MI_CpuFill8(void *dst, int value, u32 size);

void ClearBuffer(void *dst, u32 size)
{
    MI_CpuFill8(dst, 0, size);
}
