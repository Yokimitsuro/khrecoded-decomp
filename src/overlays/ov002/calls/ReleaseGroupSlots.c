#include "nitro/types.h"

typedef struct SlotGroups {
    u8 pad_000[0x74];
    u8 objSlots[22][16];
    u8 recordSlots[22][16];
    u8 pad_334[0x494 - 0x334];
    u8 counts[22];
} SlotGroups;

extern void func_0204f0d4(void *manager, int recordIndex);
extern void ObjManager_FreeSlot(void *manager, int index);

void ReleaseGroupSlots(void *manager, SlotGroups *groups)
{
    int group;
    int i;

    for (group = 0; group < 22; group++) {
        for (i = 0; i < groups->counts[group]; i++) {
            u8 objSlot = groups->objSlots[group][i];
            func_0204f0d4(manager, groups->recordSlots[group][i]);
            ObjManager_FreeSlot(manager, objSlot);
        }
    }
}
