#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void *gActorRegistry;

BOOL InitActorRegistry(void) {
    if (gActorRegistry == NULL) {
        gActorRegistry = NNSi_FndAllocFromDefaultHeap(0xc30);
    }
    MI_CpuFill8(gActorRegistry, 0, 0xc30);
    return TRUE;
}
