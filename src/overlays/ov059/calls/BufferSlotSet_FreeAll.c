#include "nitro/types.h"

typedef struct BufferSlot {
    u8 data[0x30];
} BufferSlot;

typedef struct BufferSlotSet {
    BufferSlot mainSlots[2];
    BufferSlot extraSlot;
    BufferSlot pairSlots[2];
} BufferSlotSet;

extern BOOL func_ov001_0206a918(BufferSlot *slot);
extern void BufferSlots_FreePair(BufferSlot *slots);

void BufferSlotSet_FreeAll(BufferSlotSet *set)
{
    u32 i;

    BufferSlots_FreePair(set->pairSlots);
    for (i = 0; i < 2; i++) {
        func_ov001_0206a918(&set->mainSlots[i]);
    }
    func_ov001_0206a918(&set->extraSlot);
}
