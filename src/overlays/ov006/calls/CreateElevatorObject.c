#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectClass FieldObjectClass;

typedef struct {
    u8 pad_00[0x70];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7D[9];
    s16 radius;
} ElevatorClassData;

typedef struct {
    u8 pad_00[8];
    ElevatorClassData *classData;
    u8 pad_0C[8];
    int (*update)(void *object);
    u8 shape[0x22];
    u8 classKind;
    u8 pad_3B[5];
    VecFx32 position;
    u16 timer;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 solid;
    u8 pad_54[4];
    VecFx32 center;
    u8 pad_64[9];
    u8 moving : 1;
    u8 flagsHigh : 7;
    u8 state;
} ElevatorObject;

extern ElevatorObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int priority);
extern int UpdateElevatorObject(void *object);
extern int func_ov006_020a0ce8(void *object);

ElevatorObject *CreateElevatorObject(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, const VecFx32 *offset) {
    ElevatorObject *object = FieldObject_Create(objectClass, slotIndex);
    ElevatorClassData *data = object->classData;

    if (object->classKind == 0) {
        object->moving = TRUE;
    } else {
        object->moving = FALSE;
    }
    object->position = *position;
    object->timer = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->update = object->moving ? UpdateElevatorObject : func_ov006_020a0ce8;
    VEC_Add(position, offset, &object->center);
    if (object->moving) {
        object->solid = TRUE;
        object->flags |= 0x20;
        BuildCollisionShape(object->shape, &object->position, data->shapeKind, data->sizeX, data->sizeY, data->sizeZ, object->timer, TRUE, 3);
    } else {
        object->solid = FALSE;
        object->flags |= 0x10;
        BuildCollisionShape(object->shape, &object->center, 2, data->radius, 0, 0, object->timer, TRUE, 3);
        object->state = 6;
    }
    return object;
}
