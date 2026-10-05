#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x2b];
    u8 slotIndex;
    u8 pad_34[0x38];
    s16 chainHead;
    s16 nextIndex;
} FieldObject;

extern FieldObject *func_ov001_02086384(void *owner, int index);

void LinkObjectChainTail(FieldObject *object)
{
    s16 index = object->chainHead;
    FieldObject *current;

    if (index != -1) {
        for (;;) {
            current = func_ov001_02086384(object->owner, index);
            if (current->nextIndex == -1) {
                break;
            }
            index = current->nextIndex;
        }
        object->chainHead = index;
        current->nextIndex = object->slotIndex;
        return;
    }
    object->chainHead = -1;
}
