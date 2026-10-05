#include "nitro/types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectClass {
    void (*onActivate)(FieldObject *object);
    u8 pad_04[0x7a];
    u8 flags;
    u8 activateCount;
    u8 pad_80;
    s8 seenBit;
} FieldObjectClass;

struct FieldObject {
    u8 pad_00[8];
    FieldObjectClass *objectClass;
    u8 pad_0c[0x2c];
    u8 mode;
};

extern void func_ov001_0207f078(u32 bit);

void FieldObject_Activate(FieldObject *object, u8 mode)
{
    FieldObjectClass *objectClass = object->objectClass;

    object->mode = mode;
    if (objectClass->onActivate != NULL) {
        objectClass->onActivate(object);
    }
    if (!(objectClass->flags & 1)) {
        objectClass->flags |= 1;
        if (objectClass->seenBit >= 0) {
            func_ov001_0207f078(objectClass->seenBit);
        }
    }
    objectClass->activateCount++;
}
