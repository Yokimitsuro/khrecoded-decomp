#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ResourceLoader;

typedef struct {
    void *buffer;
    u8 pad_04[8];
} OwnedBuffer;

typedef struct {
    u8 pad_0000[0xc];
    u8 resourceBuffer[0xc];
    ResourceLoader loaders[6];
    u8 pad_0150[0xcf1c - 0x150];
    OwnedBuffer buffers[4];
} SceneWork;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern void DestroyFndObjectList(void *context);
extern void FreePointerIfSet(void **ptr);
extern void FreeResourceBufferAndProbeHeap(void *buffer);

void ReleaseSceneResources(SceneWork *work)
{
    int i;

    for (i = 0; i < 6; i++) {
        CallVirtualHandlerSlot1(&work->loaders[i], 0);
        FlushBufferAndRunCallback(&work->loaders[i]);
        DestroyFndObjectList(&work->loaders[i]);
    }
    for (i = 0; i < 4; i++) {
        FreePointerIfSet(&work->buffers[i].buffer);
    }
    FreeResourceBufferAndProbeHeap(work->resourceBuffer);
}
