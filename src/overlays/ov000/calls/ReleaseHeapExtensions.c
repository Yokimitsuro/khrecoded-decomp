#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1a0];
    void *slotA;
    u8 pad_1a4[0x21c - 0x1a4];
    void *slotB;
    void *slotC;
} Heap;

extern void NNSi_FndFreeFromDefaultHeap(void *slot);

void ReleaseHeapExtensions(Heap *heap)
{
    NNSi_FndFreeFromDefaultHeap(heap->slotA);
    NNSi_FndFreeFromDefaultHeap(heap->slotB);
    NNSi_FndFreeFromDefaultHeap(heap->slotC);
}
