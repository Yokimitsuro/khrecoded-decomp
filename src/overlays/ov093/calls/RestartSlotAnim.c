#include "nitro/types.h"

typedef struct {
    int animIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x200];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[13];
} SceneWork;

extern void IndexedRecord_ClearActive(void *animSet, int index);
extern void func_0204f218(void *animSet, int index, u16 frame);

void RestartSlotAnim(int side, int slotIndex, int frame, SceneWork *work)
{
    int offset = side * 0x6434;
    u8 *animSets = work->animSets[0];
    SlotEntry *entry = side == 0 ? &work->leftSlots[slotIndex] : &work->rightSlots[slotIndex];
    IndexedRecord_ClearActive(animSets + offset, entry->animIndex);
    func_0204f218(animSets + offset, entry->animIndex, frame);
}
