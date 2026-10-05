#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct FieldObjectClass {
    u8 pad_00[0x70];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[7];
    s8 unk_84;
} FieldObjectClass;

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    void *work;
    u8 pad_10[0x4];
    void (*update)(struct FieldObject *object);
    CollisionShape shape;
    u8 pad_38[0x3];
    u8 drawFlags : 4;
    u8 drawLayer : 4;
    u8 pad_3C[0x4];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 unk_53;
    u8 pad_54[4];
    s16 linkId;
    u8 linkState;
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void func_ov001_02081750(FieldObject *object);
extern void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);

FieldObject *FieldObject_CreateLinked(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset,
                                 u8 saveBitCount, VecFx32 *position, u16 angle, s16 linkId)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);
    FieldObjectClass *def = object->objectClass;

    object->position = *position;
    object->angle = angle;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = objectClass->unk_84;
    object->drawLayer = 3;
    object->linkId = linkId;
    object->linkState = 0;
    object->update = func_ov001_02081750;
    object->flags |= 0x10;
    object->flags |= 0x20;
    object->flags |= 0x4000;
    BuildCollisionShape(&object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY,
                                 def->sizeZ, object->angle, TRUE, 3);
    return object;
}
