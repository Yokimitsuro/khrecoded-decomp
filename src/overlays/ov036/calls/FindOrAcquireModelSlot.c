#include "nitro/types.h"

typedef struct ModelSlot {
    u8 pad_000[0x12c];
    s32 ownerId;
    u8 pad_130[0x8];
} ModelSlot;

typedef struct SlotScene {
    u8 pad_0000[0x1094];
    ModelSlot *models;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;

int FindOrAcquireModelSlot(int ownerId)
{
    int i;
    int freeIndex = -1;
    ModelSlot *models = data_ov036_020c3940.scene->models;

    for (i = 0; i < 5; i++) {
        int slotOwner = models[i].ownerId;
        if (ownerId == slotOwner) {
            return i;
        }
        if (freeIndex == -1 && slotOwner == -1) {
            freeIndex = i;
        }
    }
    if (freeIndex == -1) {
        return -1;
    }
    models[freeIndex].ownerId = ownerId;
    return freeIndex;
}
