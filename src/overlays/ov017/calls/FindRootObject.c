#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x50];
    s16 parentIndex;
} FieldObject;

extern FieldObject *func_ov001_02086384(void *owner, int index);

static inline FieldObject *GetParentObject(FieldObject *object)
{
    return func_ov001_02086384(object->owner, object->parentIndex);
}

FieldObject *FindRootObject(FieldObject *object)
{
    while (object->parentIndex >= 0) {
        object = GetParentObject(object);
    }
    return object;
}
