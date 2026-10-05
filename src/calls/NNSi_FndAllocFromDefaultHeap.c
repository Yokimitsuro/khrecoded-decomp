#include "nitro/types.h"

extern int data_02060394;
extern void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, int align);

void *NNSi_FndAllocFromDefaultHeap(u32 size)
{
    void *heap = *(void **)((char *)&data_02060394 + 4);
    return NNS_FndAllocFromExpHeapEx(*(void **)heap, size, 4);
}
