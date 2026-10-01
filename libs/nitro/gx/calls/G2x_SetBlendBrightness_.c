#include "libs/nitro/os/os_types_internal.h"

void G2x_SetBlendBrightness_(u32 address, int plane, int brightness)
{
    if (brightness < 0) {
        *((volatile u16 *)address + 0) = (u16)(0xc0 | plane);
        *((volatile u16 *)address + 2) = (u16)-brightness;
    } else {
        *((volatile u16 *)address + 0) = (u16)(0x80 | plane);
        *((volatile u16 *)address + 2) = (u16)brightness;
    }
}