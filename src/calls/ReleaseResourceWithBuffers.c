#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *bufferA;
    void *bufferB;
} Resource;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees a resource and its two buffers. */
void ReleaseResourceWithBuffers(Resource **resourceHandle)
{
    Resource *resource = *resourceHandle;

    NNSi_FndFreeFromDefaultHeap(resource->bufferA);
    NNSi_FndFreeFromDefaultHeap(resource->bufferB);
    NNSi_FndFreeFromDefaultHeap(resource);
    *resourceHandle = 0;
}
