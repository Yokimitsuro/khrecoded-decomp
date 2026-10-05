#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x48];
    s8 state;
    u8 pad_51[5];
    s16 parentIndex;
} FieldObject;

extern FieldObject *func_ov001_02086384(void *owner, int index);

static inline FieldObject *GetParentObject(FieldObject *object)
{
    return func_ov001_02086384(object->owner, object->parentIndex);
}

FieldObject *FindInactiveAncestor(FieldObject *object)
{
    BOOL active;

    while (object->parentIndex >= 0) {
        object = GetParentObject(object);
        active = TRUE;
        if (object->state != 2 && object->state != 1) {
            active = FALSE;
        }
        if (!active) {
            return object;
        }
    }
    return NULL;
}
