#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x26];
    u16 flipFlags;
    u8 pad_28[0x74];
} SlotEntry;

typedef struct SlotScene {
    u8 pad_0000[0x1090];
    SlotEntry *slots;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern int func_ov036_020bb7e0(int ownerId);

void ToggleActorSlotFlip(int ownerId)
{
    SlotScene *scene = data_ov036_020c3940.scene;
    SlotEntry *slot = &scene->slots[func_ov036_020bb7e0(ownerId)];

    slot->flipFlags = slot->flipFlags == 0 ? 0x8000 : 0;
}
