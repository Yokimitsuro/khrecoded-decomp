#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct PatrolRoute {
    VecFx32 *points;
    s8 pointCount;
    s8 saveValue;
    u8 pad_06[2];
} PatrolRoute;

typedef struct FieldObjectDef {
    u8 pad_00[0x70];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct FieldEntry {
    u8 pad_000[0x1a8];
    u8 shadow[4];
} FieldEntry;

typedef struct PatrolObject PatrolObject;

struct PatrolObject {
    u8 pad_00[8];
    FieldObjectDef *def;
    FieldEntry *entry;
    u8 pad_10[4];
    void (*update)(PatrolObject *object);
    u8 shape[0x23];
    u8 flags_3b_lo : 4;
    u8 kind : 4;
    u8 pad_3c[4];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 blendIndex;
    u8 pad_54[4];
    s32 timer;
    s32 counter;
    PatrolRoute *routes;
    VecFx32 direction;
    VecFx32 up;
    s8 routeCount;
    s8 routeIndex;
    u8 pad_7e;
    s8 pointIndex;
    s8 startIndex;
    u8 state;
    u8 substate;
};

extern PatrolObject *FieldObject_Create(void *objectClass, u8 slotIndex);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void SetSavedValueFlag7(PatrolObject *object, int value);
extern void SetPackedStateLowBit(PatrolObject *object, u16 lowBit);
extern void ShadowVolume_Init(void *shadow, const VecFx32 *offset, fx32 radius, int flags);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);
extern u32 random_next_scaled(int range);
extern void FieldObject_SetSavedBits1To6(PatrolObject *object, int value);
extern BOOL DetachFromLeaderQuadTree(PatrolObject *object);
extern void UpdatePatrolIdle(PatrolObject *object);
extern const VecFx32 data_0205344c;

PatrolObject *CreatePatrolObject(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, s8 routeCount, PatrolRoute *routes)
{
    PatrolObject *object = FieldObject_Create(objectClass, slotIndex);
    FieldObjectDef *def = object->def;
    VecFx32 direction;
    VecFx32 up;

    object->position = data_0205344c;
    object->angle = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->blendIndex = 0;
    object->kind = 6;
    WriteSessionPackedBits(object->saveBitOffset, object->saveBitCount, 0);
    SetSavedValueFlag7(object, 0);
    SetPackedStateLowBit(object, 0);
    ShadowVolume_Init(object->entry->shadow, &data_0205344c, 0x99a, 0);
    BuildCollisionShape(object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, TRUE, 3);
    object->timer = 0;
    object->update = UpdatePatrolIdle;
    object->counter = 0;
    object->routes = routes;
    object->routeCount = routeCount;
    object->state = 0;
    object->substate = 0;
    object->routeIndex = random_next_scaled(object->routeCount);
    FieldObject_SetSavedBits1To6(object, object->routes[object->routeIndex].saveValue);
    if (DetachFromLeaderQuadTree(object)) {
        object->routeIndex = (object->routeIndex + 1 + random_next_scaled(object->routeCount - 1)) % object->routeCount;
    }
    FieldObject_SetSavedBits1To6(object, object->routes[object->routeIndex].saveValue);
    object->pointIndex = random_next_scaled(object->routes[object->routeIndex].pointCount);
    object->startIndex = object->pointIndex;
    object->position = object->routes[object->routeIndex].points[object->pointIndex];
    direction.x = 0;
    direction.y = 0;
    direction.z = FX32_ONE;
    object->direction = direction;
    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    object->up = up;
    object->stateFlags |= 0x10;
    object->stateFlags |= 0x20;
    return object;
}
