typedef unsigned int u32;

typedef struct NNSFndAllocator {
    const void *pFunc;
    void *pHeap;
    u32 heapParam1;
    u32 heapParam2;
} NNSFndAllocator;

extern void OS_FreeToHeap(int arena, int heap, void *block);

void AllocatorFreeForSDKHeap(NNSFndAllocator *allocator, void *block)
{
    int heap = (int)allocator->pHeap;
    int arena = (int)allocator->heapParam1;

    OS_FreeToHeap(arena, heap, block);
}
