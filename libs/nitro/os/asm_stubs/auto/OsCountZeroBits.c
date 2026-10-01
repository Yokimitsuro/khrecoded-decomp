#include "libs/nitro/os/os_vram_exclusive_internal.h"

u32 OsCountZeroBits(u32 bitmap)
{
    u32 result;
    __asm {
        clz result, bitmap
    }
    return result;
}
