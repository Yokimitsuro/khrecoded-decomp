#include "nitro/types.h"

typedef struct ObjectClass {
    u8 pad_00[0x88];
    u8 animation[4];
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    u8 pad_0c[0x58];
    s32 frame;
} FieldObject;

extern void func_ov011_020a0708(FieldObject *object, int state);
extern s32 func_0202f4cc(void *animation, int index);

int FieldObject_AdvanceToAnimEnd(FieldObject *object)
{
    ObjectClass *objectClass = object->objectClass;
    object->frame += 0x1000;
    if (object->frame + 0x1000 == func_0202f4cc(objectClass->animation, 0)) {
        func_ov011_020a0708(object, 2);
    }
    return 0;
}
