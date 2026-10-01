#include "libs/nitro/os/os_protection_region_internal.h"

void OS_SetProtectionRegionEx(OSProtectionRegion region, u32 address, u32 size)
{
    u32 shift = (size - 0x16) >> 1;
    u32 mask = (u32)-0x1000 << shift;
    u32 parameter = (address & mask) | size | 1;

    OSi_SetProtectionRegion(region, parameter);
}