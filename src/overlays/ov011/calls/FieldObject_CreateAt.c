#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectExtra {
    s32 value0;
    s32 value1;
} FieldObjectExtra;

typedef struct FieldObject {
    u8 pad_00[0x3b];
    u8 displayFlags;
    u8 pad_3C[0x04];
    VecFx32 position;
    u16 timer;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 unk_53;
    u8 pad_54[0x08];
    FieldObjectExtra extra;
} FieldObject;

extern FieldObject *FieldObject_Create(void *objectClass, u8 slotIndex);
extern void func_ov011_020a0708(FieldObject *object, int state);

FieldObject *FieldObject_CreateAt(void *objectClass, u8 slotIndex, u16 saveBitOffset,
                                           u8 saveBitCount, VecFx32 *position,
                                           FieldObjectExtra *extra)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);

    object->position = *position;
    object->timer = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = 0;
    object->flags |= 0x4000;
    object->displayFlags = (object->displayFlags & ~0xf0) | 0x40;
    func_ov011_020a0708(object, 0);
    object->extra = *extra;
    return object;
}
