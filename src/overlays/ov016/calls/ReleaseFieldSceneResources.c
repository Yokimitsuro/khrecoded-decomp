#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x60];
    s32 handles[21];
    s16 groupId;
    u8 pad_b6[2];
    void *buffer;
    void *workBuffer;
    u8 pad_c0[0xc8 - 0xc0];
    u16 slotCount : 5;
    u16 slotRest : 11;
    u8 pad_ca[2];
    void *slotBuffer;
    void *extraBuffer;
} FieldScene;

extern void ReleaseHandleIfSet(s32 *handle);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov001_020881a8(u32 slotIndex);
extern void func_ov021_020a8a88(int groupId);

void ReleaseFieldSceneResources(FieldScene *scene)
{
    int i;

    for (i = 0; i < 21; i++) {
        if (scene->handles[i] != 0) {
            ReleaseHandleIfSet(&scene->handles[i]);
        }
    }
    if (scene->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene->workBuffer);
        scene->workBuffer = NULL;
    }
    if (scene->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene->buffer);
        scene->buffer = NULL;
    }
    if (scene->slotBuffer != NULL) {
        for (i = 0; i < scene->slotCount; i++) {
            func_ov001_020881a8((u16)i);
        }
        NNSi_FndFreeFromDefaultHeap(scene->slotBuffer);
        scene->slotBuffer = NULL;
    }
    if (scene->extraBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene->extraBuffer);
        scene->extraBuffer = NULL;
    }
    if (scene->groupId != -1) {
        func_ov021_020a8a88(scene->groupId);
        scene->groupId = -1;
    }
}
