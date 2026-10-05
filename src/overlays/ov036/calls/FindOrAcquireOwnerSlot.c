#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotEntry {
    u8 pad_00[0x4];
    s16 width;
    u8 pad_06[0xa];
    fx32 posX;
    u8 pad_14[0xc];
    fx32 scale;
    u8 pad_24[0x68];
    s32 ownerId;
    s32 slotIndex;
    u8 pad_94[0x8];
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
extern void func_ov036_020bd090(int ownerId);

int FindOrAcquireOwnerSlot(int ownerId)
{
    SlotScene *scene = data_ov036_020c3940.scene;
    int freeIndex = -1;
    int i;

    for (i = 0; i < 8; i++) {
        int slotOwner = scene->slots[i].ownerId;
        if (ownerId == slotOwner) {
            return i;
        }
        if (freeIndex == -1 && slotOwner == -1) {
            freeIndex = i;
        }
    }
    if (freeIndex == -1) {
        for (i = 0; i < 8; i++) {
            SlotEntry *slot = &scene->slots[i];
            if (slot->posX <= (-slot->width >> 1) << 12 || slot->posX >= ((slot->width >> 1) + 0x100) << 12) {
                func_ov036_020bd090(slot->ownerId);
                freeIndex = i;
                break;
            }
        }
    }
    scene->slots[freeIndex].ownerId = ownerId;
    scene->slots[freeIndex].posX = -0x100000;
    scene->slots[freeIndex].slotIndex = freeIndex;
    scene->slots[freeIndex].scale = 0x1000 - (8 - freeIndex) * 0x19a;
    return freeIndex;
}
