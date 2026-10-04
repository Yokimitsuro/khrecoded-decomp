typedef unsigned int u32;

typedef struct NNSFndAllocator {
    const void *pFunc;
    void *pHeap;
    u32 heapParam1;
    u32 heapParam2;
} NNSFndAllocator;

extern void *OS_AllocFromHeap(int arena, int heap, u32 size);

void *AllocatorAllocForSDKHeap(NNSFndAllocator *allocator, u32 size)
{
    int heap = (int)allocator->pHeap;
    int arena = (int)allocator->heapParam1;

    return OS_AllocFromHeap(arena, heap, size);
}
