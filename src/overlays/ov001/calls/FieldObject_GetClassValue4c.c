#include "nitro/types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x4c];
    s32 value4c;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
    u8 pad_0C[0x42];
    u16 flags;
} FieldObject;

extern BOOL IsObjectFlagClear(FieldObject *object);

s32 FieldObject_GetClassValue4c(FieldObject *object)
{
    if (!IsObjectFlagClear(object) || !(object->flags & 0x10)) {
        return -1;
    }
    return object->objectClass->value4c;
}
