#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct FieldObjectDef {
    u8 pad_00[0x64];
    s16 actorKind;
    u8 pad_66[0x0A];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    u8 pad_0c[0x0C];
    CollisionShape shape;
    u8 actorId;
    u8 pad_39[0x07];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x28];
    VecFx32 anchor;
} FieldObject;

extern void *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);

void FieldObject_MoveWithAnchor(FieldObject *object, const VecFx32 *position)
{
    FieldObjectDef *def = object->def;
    VecFx32 offset;

    VEC_Subtract(&object->anchor, &object->position, &offset);
    VEC_Add(position, &offset, &object->anchor);
    object->position = *position;
    if ((object->stateFlags & 4) && object->def->actorKind >= 0) {
        Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), &object->position);
        BuildCollisionShape(&object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, FALSE, 3);
    }
}
