#ifndef NITRO_MI_H
#define NITRO_MI_H

#include "nitro/types.h"
#include "nitro/hw.h"

typedef enum MICartridgeRomCycle1st {
    MI_CTRDG_ROMCYCLE1_10 = 0,
    MI_CTRDG_ROMCYCLE1_8,
    MI_CTRDG_ROMCYCLE1_6,
    MI_CTRDG_ROMCYCLE1_18
} MICartridgeRomCycle1st;

typedef enum MICartridgeRomCycle2nd {
    MI_CTRDG_ROMCYCLE2_6 = 0,
    MI_CTRDG_ROMCYCLE2_4
} MICartridgeRomCycle2nd;

typedef enum MIProcessor {
    MI_PROCESSOR_ARM9 = 0,
    MI_PROCESSOR_ARM7
} MIProcessor;

typedef void *(*MIAllocatorAllocFunction)(void *userData, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void *userData, void *buffer);

typedef struct MIAllocator {
    void *userData;
    MIAllocatorAllocFunction alloc;
    MIAllocatorFreeFunction free;
} MIAllocator;

#define MI_CpuClear8(destination, size) MI_CpuFill8((destination), 0, (size))

#endif
