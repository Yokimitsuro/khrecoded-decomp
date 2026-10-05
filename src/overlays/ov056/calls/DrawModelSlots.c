#include "nitro/types.h"

typedef struct ModelSlot {
    u8 pad_000[0x130];
    void *node;
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
} ModelSlotList;

extern void func_01ffb12c(ModelSlot *slot);

void DrawModelSlots(ModelSlotList *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        if (list->slots[i].node != NULL) {
            func_01ffb12c(&list->slots[i]);
        }
    }
}
