#include "nitro/types.h"

u32 AlignUpTo4K_020c02f4(u32 size)
{
    if (size & 0xfff) {
        size = (size & ~0xfff) + 0x1000;
    }
    return size;
}
