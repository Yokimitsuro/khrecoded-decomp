#include "nitro/types.h"

typedef struct {
    void *data;
    u8 pad[4];
} Buffer;

typedef struct {
    u8 pad_00[0xc];
    u8 *owner;
    u8 pad_10[0x60 - 0x10];
    Buffer *buffers;
    u8 pad_64[0x7c - 0x64];
    s8 bufferCount;
} Loader;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int FSi_DefaultStepDoneA(void *task);
extern void func_ov001_0207f26c(Loader *self);

void FreeLoaderBuffers(Loader *loader) {
    s8 count = loader->bufferCount;
    s8 i;
    for (i = 0; i < count; i++) {
        NNSi_FndFreeFromDefaultHeap(loader->buffers[i].data);
    }
    NNSi_FndFreeFromDefaultHeap(loader->buffers);
    FSi_DefaultStepDoneA(loader->owner + 0x1a8);
    func_ov001_0207f26c(loader);
}
