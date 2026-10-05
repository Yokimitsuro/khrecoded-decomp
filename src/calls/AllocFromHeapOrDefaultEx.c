#include "nitro/types.h"

extern int data_02060394;
extern void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, int align);

void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap)
{
    if (heap == 0) {
        heap = *(void ***)((char *)&data_02060394 + 4);
    }
    return NNS_FndAllocFromExpHeapEx(*heap, size, align);
}
