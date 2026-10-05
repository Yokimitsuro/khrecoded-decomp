#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *heapBlock;
} Ov045HeapHolder;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees a held heap block and clears it. */
void ReleaseHeapBlockIfAllocated(Ov045HeapHolder *holder)
{
    if (holder->heapBlock != NULL) {
        NNSi_FndFreeFromDefaultHeap(holder->heapBlock);
        holder->heapBlock = NULL;
    }
}
