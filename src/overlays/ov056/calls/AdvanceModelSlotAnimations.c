#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelSlot {
    u8 pad_000[0x130];
    void *node;
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern u16 AdvanceAnimationTracks(ModelSlot *state, fx32 delta);

void AdvanceModelSlotAnimations(ModelSlotList *list, fx32 delta)
{
    int i;
    for (i = 0; i < list->count; i++) {
        ModelSlot *slot = &list->slots[i];
        if (slot->node != NULL && AdvanceAnimationTracks(slot, delta)) {
            slot->node = NULL;
        }
    }
}
