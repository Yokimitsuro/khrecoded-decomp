#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ObjectList;

typedef struct {
    void *ptr;
    u8 rest[8];
} OwnedBuffer;

typedef struct {
    u8 pad0[0x14];
    u8 resource[0xc];
    ObjectList lists[4];
    u8 pad1[0x110e8 - 0x20 - 4 * 0x34];
    OwnedBuffer buffers[2];
} ScreenWork;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern BOOL DestroyFndObjectList(void *container);
extern void FreePointerIfSet(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap(void *resource);

void ReleaseScreenResources_020bf9c8(ScreenWork *work) {
    int i;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1(&work->lists[i], 0);
        FlushBufferAndRunCallback(&work->lists[i]);
        DestroyFndObjectList(&work->lists[i]);
    }
    for (i = 0; i < 2; i++) {
        FreePointerIfSet(&work->buffers[i]);
    }
    FreeResourceBufferAndProbeHeap(work->resource);
}