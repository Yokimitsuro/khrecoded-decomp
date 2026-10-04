typedef unsigned int u32;

typedef struct NNSFndAllocator {
    const void *pFunc;
    void *pHeap;
    u32 heapParam1;
    u32 heapParam2;
} NNSFndAllocator;

extern void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, int alignment);

void *AllocatorAllocForExpHeap(NNSFndAllocator *allocator, u32 size)
{
    return NNS_FndAllocFromExpHeapEx(
        allocator->pHeap,
        size,
        allocator->heapParam1
    );
}
