#include "nitro/types.h"

typedef struct ModelSlot {
    u8 data[0x134];
} ModelSlot;

typedef struct ModelSlotList {
    ModelSlot *slots;
    s8 count;
    u8 loadMode;
} ModelSlotList;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_ov056_020d42c8(ModelSlot *slot, u32 fileIndex, int loadMode);

void AllocModelSlots(ModelSlotList *list, u32 fileIndex, s8 count, int loadMode)
{
    int i = 0;
    list->count = count;
    list->slots = NULL;
    list->loadMode = loadMode;
    if (list->count > 0) {
        list->slots = NNSi_FndAllocFromDefaultHeap(list->count * sizeof(ModelSlot));
        for (; i < list->count; i++) {
            func_ov056_020d42c8(&list->slots[i], fileIndex, loadMode);
        }
    }
}
