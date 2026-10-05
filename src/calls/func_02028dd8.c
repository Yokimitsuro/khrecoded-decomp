#include "nitro/types.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 len);

void func_02028dd8(u16 *state, const void *src)
{
    MI_CpuCopy8(src, state, 4);
    state[1] = (state[1] & ~1) | 1;
    *state = *state & ~0xffe0;
}
