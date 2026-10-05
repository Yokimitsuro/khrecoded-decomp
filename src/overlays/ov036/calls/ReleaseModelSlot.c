#include "nitro/types.h"

typedef struct ModelSlot {
    u8 pad_000[0x24];
    u8 resource[0x74];
    s32 isLoaded;
    u8 pad_09C[0x90];
    s32 ownerId;
    u8 pad_130[0x4];
    s32 releasePending;
} ModelSlot;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    s32 isBusy;
    u8 pad_0C84[0x410];
    ModelSlot *models;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern int FindOrAcquireModelSlot(int ownerId);
extern void ReleaseResourceAndDetach(void *resource);
extern void MI_CpuFill8(void *dst, int value, u32 size);

void ReleaseModelSlot(int ownerId, int mode)
{
    SlotScene *scene = data_ov036_020c3940.scene;
    int index = FindOrAcquireModelSlot(ownerId);
    ModelSlot *slot;

    if (index == -1) {
        return;
    }
    slot = &scene->models[index];
    if (slot->isLoaded == 0) {
        return;
    }
    if (scene->isBusy != 0) {
        mode = 0;
    }
    switch (mode) {
    case 0:
        ReleaseResourceAndDetach(slot->resource);
        MI_CpuFill8(slot, 0, sizeof(ModelSlot));
        slot->ownerId = -1;
        break;
    case 1:
        slot->releasePending = 1;
        break;
    }
}
