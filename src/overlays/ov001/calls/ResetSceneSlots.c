#include "nitro/types.h"

typedef struct SceneItemTable {
    u8 pad_00[8];
    void *items[1];
} SceneItemTable;

typedef struct SceneSlot {
    u8 state;
    u8 pad_01[3];
    u32 resource;
    u32 size;
    u32 extra;
} SceneSlot;

typedef struct SceneSlots {
    SceneItemTable *table;
    u8 pad_0004[9];
    s8 selected;
    u8 pad_000E[0x108a];
    SceneSlot slots[2];
    u8 slotsReady;
    u8 slotsBusy;
} SceneSlots;

extern SceneSlots *data_ov001_020a048c;
extern void LoadNextSceneSlotResources(SceneSlot *slot, void *item, SceneSlots *scene);

void ResetSceneSlots(void)
{
    SceneSlots *scene = data_ov001_020a048c;
    int i;

    scene->slotsBusy = 0;
    scene->slotsReady = 1;
    for (i = 0; i < 2; i++) {
        SceneSlot *slot = &scene->slots[i];

        slot->state = 0;
        slot->resource = 0;
        slot->size = 0;
        slot->extra = 0;
        LoadNextSceneSlotResources(slot, data_ov001_020a048c->table->items[scene->selected], scene);
    }
}
