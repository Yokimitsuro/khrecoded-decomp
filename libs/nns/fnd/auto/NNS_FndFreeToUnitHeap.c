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

void NNS_FndFreeToUnitHeap(
    NNSiFndUntHeap *heap,
    NNSiFndUntHeapMBlockHead *block
)
{
    block->next = heap->freeList.head;
    heap->freeList.head = block;
}
