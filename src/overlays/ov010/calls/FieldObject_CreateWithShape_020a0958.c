#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    u8 pad_00[0x20];
} CollisionShape;

typedef struct FieldObjectClass {
    u8 pad_00[0x70];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[7];
    s8 blendIndex;
} FieldObjectClass;

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    u8 *work;
    u8 pad_10[4];
    void *stateHandler;
    CollisionShape shape;
    u8 pad_38[3];
    u8 layerLow : 4;
    u8 layerHigh : 4;
    u8 pad_3c[4];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 blendIndex;
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, int slotIndex);
extern void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);
extern void Actor_CheckProximityTrigger(void);

FieldObject *FieldObject_CreateWithShape_020a0958(FieldObjectClass *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, u16 angle)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);
    FieldObjectClass *def = object->objectClass;

    object->position = *position;
    object->angle = angle;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->blendIndex = objectClass->blendIndex;
    object->layerHigh = 0;
    object->stateHandler = Actor_CheckProximityTrigger;
    BuildCollisionShape(&object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, TRUE, 3);
    return object;
}
