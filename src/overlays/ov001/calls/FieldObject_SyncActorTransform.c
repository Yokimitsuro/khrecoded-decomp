#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 kind;
    u8 box[0x1c];
    VecFx32 delta;
    u8 sweptBox[0x18];
} CollisionShape;

typedef struct {
    u16 flags;
    u8 pad_02[0x7a];
    u16 rotation;
} ActorState;

typedef struct {
    u8 pad_000[0x10];
    u32 actorHeader;
    ActorState state;
    u8 pad_092[0x140 - 0x92];
    CollisionShape shape;
} FieldObjectWork;

typedef struct {
    u8 pad_00[0xc];
    FieldObjectWork *work;
    u8 pad_10[0x30];
    VecFx32 position;
    u16 rotation;
} FieldObject;

extern void Obj_SetPosition(void *actor, const VecFx32 *position);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);

void FieldObject_SyncActorTransform(FieldObject *object)
{
    VecFx32 shapePos;
    VecFx32 raised;
    CollisionShape *shape;
    ActorState *state;

    Obj_SetPosition(&object->work->actorHeader, &object->position);
    raised.x = object->position.x;
    raised.y = object->position.y + 0xccd;
    raised.z = object->position.z;
    shapePos = raised;
    shape = &object->work->shape;
    SetShapePosition(shape, &shapePos);
    OffsetBoxByDelta(shape->box, shape->sweptBox, &shape->delta);
    state = &object->work->state;
    state->rotation = object->rotation;
    state->flags |= 0x20;
}
