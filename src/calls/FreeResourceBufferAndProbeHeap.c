#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *buffer;
} FreeableResource;

extern void **data_0206039c;
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int findLargestAlignedHeapBlock(void *heap, int alignmentInput);

BOOL FreeResourceBufferAndProbeHeap(FreeableResource *resource)
{
    NNSi_FndFreeFromDefaultHeap(resource->buffer);
    findLargestAlignedHeapBlock(*data_0206039c, 4);
    return TRUE;
}
