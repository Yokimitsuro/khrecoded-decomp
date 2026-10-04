typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void *heapStart;
    void *heapEnd;
    u32 attribute;
} NNSiFndHeapHead;

typedef NNSiFndHeapHead *NNSFndHeapHandle;

typedef struct NNSiFndUntHeapHead {
    void *freeListHead;
    u32 blockSize;
} NNSiFndUntHeapHead;

typedef struct NNSFndAllocator {
    const void *pFunc;
    NNSFndHeapHandle pHeap;
    u32 heapParam1;
    u32 heapParam2;
} NNSFndAllocator;

extern void *NNS_FndAllocFromUnitHeap(NNSFndHeapHandle heap);

void *AllocatorAllocForUnitHeap(NNSFndAllocator *allocator, u32 size)
{
    NNSFndHeapHandle heap = allocator->pHeap;
    NNSiFndUntHeapHead *unitHeap;

    unitHeap = (NNSiFndUntHeapHead *)((u8 *)heap + sizeof(NNSiFndHeapHead));
    if (size > unitHeap->blockSize) {
        return 0;
    }

    return NNS_FndAllocFromUnitHeap(heap);
}
