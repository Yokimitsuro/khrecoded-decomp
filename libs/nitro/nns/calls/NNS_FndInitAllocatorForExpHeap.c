typedef unsigned int u32;

typedef struct NNSFndAllocatorFunc NNSFndAllocatorFunc;

typedef struct NNSFndAllocator {
    const NNSFndAllocatorFunc *pFunc;
    void *pHeap;
    u32 heapParam1;
    u32 heapParam2;
} NNSFndAllocator;

extern const NNSFndAllocatorFunc sAllocatorFuncForExpHeap;

void NNS_FndInitAllocatorForExpHeap(
    NNSFndAllocator *allocator,
    void *heap,
    int alignment
)
{
    allocator->pFunc = &sAllocatorFuncForExpHeap;
    allocator->pHeap = heap;
    allocator->heapParam1 = alignment;
    allocator->heapParam2 = 0;
}
