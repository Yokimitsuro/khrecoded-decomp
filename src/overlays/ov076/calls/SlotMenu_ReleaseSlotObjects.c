#include "nitro/types.h"

typedef struct SlotObject {
    s32 objectId;
    u8 pad_04[0x14];
} SlotObject;

typedef struct SlotMenu {
    u8 pad_00000[0x1b928];
    SlotObject slotObjects[8][18];
    SlotObject extraObjects[4];
} SlotMenu;

extern void *func_ov039_020bc1dc(void);
extern void func_0204f0d4(void *objectManager, int objectId);

void SlotMenu_ReleaseSlotObjects(SlotMenu *menu)
{
    void *objectManager = func_ov039_020bc1dc();
    int slot;
    int i;

    for (slot = 0; slot < 8; slot++) {
        for (i = 0; i < 18; i++) {
            func_0204f0d4(objectManager, menu->slotObjects[slot][i].objectId);
            menu->slotObjects[slot][i].objectId = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        func_0204f0d4(objectManager, menu->extraObjects[i].objectId);
        menu->extraObjects[i].objectId = -1;
    }
}
