#include "nitro/types.h"

typedef struct {
    u8 data[0x2c];
} SharedRecordState;

typedef struct {
    u8 pad_000[0x15];
    u8 partCount;
    u8 pad_016[0x2e];
    u8 resource[0x104];
    SharedRecordState mainState;
    SharedRecordState *partStates;
} SceneObject;

extern void ReleaseResourceAndDetach(u8 *object);
extern void ReleaseSharedRecordState(SharedRecordState *state);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseCallbackOwnedBuffer(SceneObject *object);

void ReleaseSceneObject(SceneObject *object)
{
    int i;

    ReleaseResourceAndDetach(object->resource);
    ReleaseSharedRecordState(&object->mainState);
    if (object->partStates != NULL) {
        for (i = 0; i < object->partCount; i++) {
            ReleaseSharedRecordState(&object->partStates[i]);
        }
        NNSi_FndFreeFromDefaultHeap(object->partStates);
    }
    ReleaseCallbackOwnedBuffer(object);
}
