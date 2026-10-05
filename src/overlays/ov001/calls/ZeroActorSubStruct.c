#include "nitro/types.h"

extern void MI_CpuFill8(void *dst, u32 value, u32 size);

void ZeroActorSubStruct(void *block)
{
    MI_CpuFill8(block, 0, 0x30);
}
