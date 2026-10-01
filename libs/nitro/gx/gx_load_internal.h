#ifndef GX_LOAD_INTERNAL_H
#define GX_LOAD_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

extern u32 GXi_DmaId;
extern void MIi_DmaCopy16(u32 channel, const void *source, void *destination,
                          u32 size, BOOL enable);
extern void MIi_DmaCopy32(u32 channel, const void *source, void *destination,
                          u32 size, BOOL enable);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuCopy32(const void *source, void *destination, u32 size);

static inline void GXi_DmaCopy16(u32 channel, const void *source,
                                 void *destination, u32 size)
{
    if (channel != (u32)-1 && size > 0x1c) {
        MIi_DmaCopy16(channel, source, destination, size, 1);
    } else {
        MIi_CpuCopy16(source, destination, size);
    }
}

static inline void GXi_DmaCopy32(u32 channel, const void *source,
                                 void *destination, u32 size)
{
    if (channel != (u32)-1 && size > 0x30) {
        MIi_DmaCopy32(channel, source, destination, size, 1);
    } else {
        MIi_CpuCopy32(source, destination, size);
    }
}

#endif
