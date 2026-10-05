#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void *data_0206083c;

BOOL InitActorRegistry(void) {
    if (data_0206083c == NULL) {
        data_0206083c = NNSi_FndAllocFromDefaultHeap(0xc30);
    }
    MI_CpuFill8(data_0206083c, 0, 0xc30);
    return TRUE;
}
