#include "libs/nitro/os/os_types_internal.h"

typedef u16 GXRgb;

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

void G3X_SetToonTable(const GXRgb *rgbTable)
{
    MIi_CpuCopy16(rgbTable, (void *)0x04000380, 64);
}
