#include "nitro/types.h"

typedef struct SlotNode {
    struct SlotNode *next;
    u32 slot : 8;
    u32 : 24;
} SlotNode;

typedef struct SlotList {
    SlotNode *head;
} SlotList;

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x2b];
    u8 slotIndex;
} FieldObject;

extern void *func_ov001_02086384(void *owner, int index);

void *FindSlotLinkedObject(SlotList *list, FieldObject *object)
{
    SlotNode *node;

    for (node = list->head; node != NULL; node = node->next) {
        if (object->slotIndex == node->slot) {
            return func_ov001_02086384(object->owner, node->slot);
        }
    }
    return NULL;
}
