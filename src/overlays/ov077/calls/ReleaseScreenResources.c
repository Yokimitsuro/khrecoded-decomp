#include "nitro/types.h"

typedef struct ScreenWork {
    u8 pad_00000[0x10];
    void *buffer0;
    void *buffer1;
    void *container;
    u8 pad_0001C[0x18];
    u8 unk_00034[0x6c0];
    u8 sceneObject[0x4768];
    void *messageData;
    u8 pad_04E60[0xcda0];
    void *heapBlock;
} ScreenWork;

extern BOOL ReleaseRecordSlot(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int ZeroHalfThenFree(void *buffer);
extern void ReleaseResourceAndDetach(void *object);
extern void func_ov077_020c9f7c(void *object);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void FreePointerIfSet(void **ptr);
extern void SetSecondaryElementEnabled(BOOL enabled);

void ReleaseScreenResources(ScreenWork *work)
{
    void *container = work->container;

    ReleaseRecordSlot(1);
    ReleaseRecordSlot(0);
    NNSi_FndFreeFromDefaultHeap(work->heapBlock);
    ZeroHalfThenFree(work->buffer1);
    ZeroHalfThenFree(work->buffer0);
    ReleaseResourceAndDetach(work->sceneObject);
    func_ov077_020c9f7c(work->unk_00034);
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    FreePointerIfSet(&work->messageData);
    SetSecondaryElementEnabled(TRUE);
}
