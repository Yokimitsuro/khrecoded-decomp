#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotEntry {
    u8 pad_00[0x20];
    fx32 scale;
    u8 pad_24[0x68];
    s32 ownerId;
    s32 slotIndex;
    u8 pad_94[0x8];
} SlotEntry;

typedef struct SlotTransition {
    u8 pad_00[0x30];
    s32 frame;
    s32 frameStep;
    s32 isOpen;
    s32 unk_3C;
} SlotTransition;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    s32 skipAnimation;
    u8 pad_0c84[0x40c];
    SlotEntry *slots;
    u8 pad_1094[0x8];
    SlotTransition transition;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;

void AdvanceSlotTransition(void)
{
    int i;
    SlotTransition *transition;
    SlotScene *scene = data_ov036_020c3940.scene;

    transition = &scene->transition;
    transition->frame += transition->frameStep;
    if (data_ov036_020c3940.scene->skipAnimation == 0 && transition->frame > 0 && transition->frame < 0x18) {
        return;
    }
    transition->frame = transition->isOpen ? 0x18 : 0;
    transition->unk_3C = 0;
    if (transition->isOpen != 0) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (scene->slots[i].ownerId != -1) {
            scene->slots[i].scale = 0x1000 - (8 - scene->slots[i].slotIndex) * 0x19a;
        }
    }
}
