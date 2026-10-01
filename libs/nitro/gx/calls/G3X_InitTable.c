#include "libs/nitro/os/os_types_internal.h"

typedef void (*MIDmaCallback)(void *);

extern u32 GXi_DmaId;
extern void MIi_DmaFill32Async(u32 dmaNo, void *destination, u32 data,
                               u32 size, MIDmaCallback callback, void *arg,
                               BOOL enable);
extern void MIi_DmaFill32(u32 dmaNo, void *destination, u32 data,
                          u32 size, BOOL enable);
extern void MIi_CpuClear32(u32 data, void *destination, u32 size);

static inline void MI_DmaFill32Async(u32 dmaNo, void *destination, u32 data,
                                     u32 size, MIDmaCallback callback, void *arg)
{
    MIi_DmaFill32Async(dmaNo, destination, data, size, callback, arg, 1);
}

static inline void MI_DmaFill32(u32 dmaNo, void *destination, u32 data, u32 size)
{
    MIi_DmaFill32(dmaNo, destination, data, size, 1);
}

static inline void MI_CpuFill32(void *destination, u32 data, u32 size)
{
    MIi_CpuClear32(data, destination, size);
}

void G3X_InitTable(void)
{
    int i;

    if (GXi_DmaId != (u32)-1) {
        MI_DmaFill32Async(GXi_DmaId, (void *)0x04000330, 0, 16, 0, 0);
        MI_DmaFill32(GXi_DmaId, (void *)0x04000360, 0, 96);
    } else {
        MI_CpuFill32((void *)0x04000330, 0, 16);
        MI_CpuFill32((void *)0x04000360, 0, 96);
    }

    for (i = 0; i < 32; ++i) {
        *(volatile u32 *)0x040004d0 = 0;
    }
}
