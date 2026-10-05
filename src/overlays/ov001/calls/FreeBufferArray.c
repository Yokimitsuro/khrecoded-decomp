#include "nitro/types.h"

typedef struct BufferArrayOwner {
    u8 pad_000[0x10c];
    int count;
    void **buffers;
} BufferArrayOwner;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeBufferArray(BufferArrayOwner *owner)
{
    int i;

    for (i = 0; i < owner->count; i++) {
        NNSi_FndFreeFromDefaultHeap(owner->buffers[i]);
    }
    NNSi_FndFreeFromDefaultHeap(owner->buffers);
}
