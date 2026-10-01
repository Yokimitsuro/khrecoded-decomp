#include "libs/nitro/os/os_types_internal.h"

s32 GX_VBlankIntr(BOOL enable)
{
    volatile u16 *displayStatus = (volatile u16 *)0x04000004;
    s32 previous = *displayStatus & 8;

    if (enable) {
        *displayStatus |= 8;
    } else {
        *displayStatus &= (u16)~8;
    }
    return previous;
}