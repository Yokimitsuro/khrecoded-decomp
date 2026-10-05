#include "nitro/types.h"

typedef struct ModelSlot {
    u8 pad_000[0x104];
    u8 recordState[0x134 - 0x104];
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern void ReleaseResourceAndDetach(u8 *object);
extern void func_ov021_020a90a4(void *state);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeModelSlots(ModelSlotList *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        ModelSlot *slot = &list->slots[i];
        ReleaseResourceAndDetach((u8 *)slot);
        func_ov021_020a90a4(slot->recordState);
    }
    if (list->slots != NULL) {
        NNSi_FndFreeFromDefaultHeap(list->slots);
    }
}
