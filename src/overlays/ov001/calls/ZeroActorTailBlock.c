#include "nitro/types.h"

extern void func_01ff88c4(void *dst, u32 value, u32 size);

void ZeroActorTailBlock(void *block)
{
    func_01ff88c4(block, 0, 0x3c8);
}
