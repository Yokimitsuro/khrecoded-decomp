#include "libs/nitro/os/os_types_internal.h"

void G2x_SetBlendBrightnessExt_(u32 address, int plane1, int plane2,
                   int ev1, int ev2, int brightness)
{
    *((volatile u16 *)address + 1) = (u16)(ev1 | (ev2 << 8));

    if (brightness < 0) {
        *((volatile u16 *)address + 0) =
            (u16)(0xc0 | plane1 | (plane2 << 8));
        *((volatile u16 *)address + 2) = (u16)-brightness;
    } else {
        *((volatile u16 *)address + 0) =
            (u16)(0x80 | plane1 | (plane2 << 8));
        *((volatile u16 *)address + 2) = (u16)brightness;
    }
}