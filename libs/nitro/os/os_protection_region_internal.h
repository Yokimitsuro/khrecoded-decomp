#ifndef NITRO_OS_PROTECTION_REGION_INTERNAL_H
#define NITRO_OS_PROTECTION_REGION_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef enum OSProtectionRegion {
    OS_PROTECTION_REGION_0,
    OS_PROTECTION_REGION_1,
    OS_PROTECTION_REGION_2,
    OS_PROTECTION_REGION_3,
    OS_PROTECTION_REGION_4,
    OS_PROTECTION_REGION_5,
    OS_PROTECTION_REGION_6,
    OS_PROTECTION_REGION_7
} OSProtectionRegion;

void OS_EnableICacheForProtectionRegion(u32 flags);
void OS_DisableICacheForProtectionRegion(u32 flags);
void OS_EnableDCacheForProtectionRegion(u32 flags);
void OS_DisableDCacheForProtectionRegion(u32 flags);
void OS_SetDPermissionsForProtectionRegion(u32 setMask, u32 flags);
void OS_EnableWriteBufferForProtectionRegion(u32 flags);
void OS_DisableWriteBufferForProtectionRegion(u32 flags);
void OSi_SetProtectionRegion(OSProtectionRegion region, u32 parameter);
void OS_SetProtectionRegionEx(OSProtectionRegion region, u32 address, u32 size);

#endif