#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x84];
    s8 unk_84;
} FieldObjectClass;

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    void *work;
    u8 pad_10[0x4];
    void (*update)(struct FieldObject *object);
    u8 pad_18[0x23];
    u8 drawFlags : 4;
    u8 drawLayer : 4;
    u8 pad_3C[0x4];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 unk_53;
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void func_ov001_02080a9c(FieldObject *object);

FieldObject *FieldObject_CreateWithUpdater(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset,
                                                    u8 saveBitCount, VecFx32 *position, u16 angle)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);

    object->position = *position;
    object->angle = angle;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = objectClass->unk_84;
    object->drawLayer = 0;
    object->update = func_ov001_02080a9c;
    return object;
}
