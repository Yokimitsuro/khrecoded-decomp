#include "nitro/types.h"

typedef struct {
    void *data;
    u8 pad_04[0xC];
} EntryBuffer;

typedef struct {
    u8 pad_000[0x130];
    EntryBuffer buffers[5];
} EntryViewer;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeEntryBuffers(EntryViewer *viewer)
{
    int bufferIndex;

    for (bufferIndex = 0; bufferIndex < 5; bufferIndex++) {
        if (viewer->buffers[bufferIndex].data != NULL) {
            NNSi_FndFreeFromDefaultHeap(viewer->buffers[bufferIndex].data);
        }
    }
}
