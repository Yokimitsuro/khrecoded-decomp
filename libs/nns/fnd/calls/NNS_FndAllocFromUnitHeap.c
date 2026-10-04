typedef unsigned char u8;
typedef unsigned int u32;

typedef struct NNSiFndUntHeapMBlockHead {
    struct NNSiFndUntHeapMBlockHead *next;
} NNSiFndUntHeapMBlockHead;

typedef struct NNSiFndUntMBlockList {
    NNSiFndUntHeapMBlockHead *head;
} NNSiFndUntMBlockList;

typedef struct NNSiFndUntHeap {
    u8 heapHead[0x20];
    u32 flags;
    NNSiFndUntMBlockList freeList;
    u32 blockSize;
} NNSiFndUntHeap;

extern NNSiFndUntHeapMBlockHead *PopMBlock(NNSiFndUntMBlockList *list);
extern void MIi_CpuClear32(u32 data, void *destination, u32 size);

void *NNS_FndAllocFromUnitHeap(NNSiFndUntHeap *heap)
{
    void *block = PopMBlock(&heap->freeList);

    if (block != 0) {
        u8 flags = heap->flags;
        u32 blockSize = heap->blockSize;

        if (flags & 1) {
            MIi_CpuClear32(0, block, blockSize);
        }
    }

    return block;
}
