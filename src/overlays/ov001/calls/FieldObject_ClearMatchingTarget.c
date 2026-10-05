#include "nitro/types.h"

typedef struct ObjectData {
    u8 pad_00[0xbc];
    s8 targetIndex;
} ObjectData;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectData *data;
    u8 pad_0c[0x2e];
    u8 index;
} FieldObject;

extern void ReleaseOwnerResource(FieldObject *object, int arg);

void FieldObject_ClearMatchingTarget(FieldObject *object, int arg)
{
    ObjectData *data = object->data;

    if (data->targetIndex == object->index) {
        data->targetIndex = -1;
    }
    ReleaseOwnerResource(object, arg);
}
