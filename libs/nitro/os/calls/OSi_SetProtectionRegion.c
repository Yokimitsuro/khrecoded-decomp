#include "libs/nitro/os/os_protection_region_internal.h"

typedef void (*ProtectionRegionSetter)(u32 parameter);
extern ProtectionRegionSetter OSi_ProtectionRegionSetters[];

void OSi_SetProtectionRegion(OSProtectionRegion region, u32 parameter)
{
    OSi_ProtectionRegionSetters[region](parameter);
}