typedef struct NNSiMemRegion {
    void *start;
    void *end;
} NNSiMemRegion;

typedef struct NNSiFndExpHeapMBlockHead {
    unsigned short signature;
    unsigned short attribute;
    unsigned int blockSize;
    struct NNSiFndExpHeapMBlockHead *previous;
    struct NNSiFndExpHeapMBlockHead *next;
} NNSiFndExpHeapMBlockHead;

extern void GetRegionOfMBlock(
    NNSiMemRegion *region,
    NNSiFndExpHeapMBlockHead *block);
extern NNSiFndExpHeapMBlockHead *RemoveMBlock(
    void *list,
    NNSiFndExpHeapMBlockHead *block);
extern int RecycleRegion();

void NNS_FndFreeToExpHeap(void *heap, void *memory)
{
    NNSiMemRegion *regionPointer;
    NNSiFndExpHeapMBlockHead *block;
    NNSiMemRegion region;
    void *heapPointer;

    block = (NNSiFndExpHeapMBlockHead *)((char *)memory - sizeof(*block));
    regionPointer = &region;
    heapPointer = heap;
    GetRegionOfMBlock(regionPointer, block);
    RemoveMBlock((char *)heapPointer + 0x2c, block);
    asm {
        mov r1, regionPointer
    }
    RecycleRegion((char *)heapPointer + 0x24);
}