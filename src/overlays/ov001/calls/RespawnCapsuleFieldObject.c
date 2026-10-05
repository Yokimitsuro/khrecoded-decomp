#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct ShapeBase {
    void *data;
    s32 bounds[6];
    s32 kind;
} ShapeBase;

typedef struct CollisionShape {
    ShapeBase base;
    VecFx32 delta;
    s32 sweptBounds[6];
} CollisionShape;

typedef struct ActorBody {
    u8 pad_000[0x140];
    CollisionShape shape;
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ActorBody *body;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x03];
    s8 blendIndex;
    u8 pad_54[0x13];
    u8 lowBits : 2;
    u8 alpha : 6;
    s32 timer68;
    u8 pad_6c[0x0c];
    s32 timer78;
} FieldObject;

typedef struct ContactHandler {
    void (*callback)(void);
    FieldObject *owner;
} ContactHandler;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x76];
    void *model;
    u16 angle;
    u8 pad_082[0xfa];
    ContactHandler handler;
} FieldActor;

extern BOOL func_ov001_020807b4(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void InitCapsuleShape(ShapeBase *shape, void *capsule, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void SetActorExtraPosition(int index, void *owner, int a2);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);
extern void func_ov001_020809f8(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void func_ov001_02083334(void);
extern const VecFx32 data_0205344c;

void RespawnCapsuleFieldObject(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams params;
    FieldActor *actor;
    u16 angle;
    VecFx32 bottomCopy;
    VecFx32 topCopy;
    VecFx32 bottom;
    VecFx32 top;
    VecFx32 axis;
    VecFx32 diff;
    void *capsule;
    ShapeBase base;
    CollisionShape shape;
    ContactHandler handler;

    func_ov001_020807b4(object->body, object->group, object->index, object->actorId, &params, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    Obj_SetPosition(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    top.x = object->position.x;
    top.y = object->position.y + 0x2333;
    top.z = object->position.z;
    topCopy = top;
    bottom.x = object->position.x;
    bottom.y = object->position.y + 0xccd;
    bottom.z = object->position.z;
    bottomCopy = bottom;
    capsule = object->body->shape.base.data;
    func_01ff9e3c(&topCopy, &bottomCopy, &diff);
    axis = diff;
    InitCapsuleShape(&base, capsule, &bottomCopy, &topCopy, &axis, func_01ffaff4(&axis, &axis), 0xccd);
    shape.base = base;
    shape.delta = data_0205344c;
    OffsetBoxByDelta(shape.base.bounds, shape.sweptBounds, &shape.delta);
    object->body->shape = shape;
    handler.callback = func_ov001_02083334;
    handler.owner = object;
    actor->handler = handler;
    SetActorExtraPosition(object->actorId, object, 0x15);
    object->timer68 = 0;
    object->alpha = 0;
    object->timer78 = 0;
    NNS_G3dMdlSetMdlAlphaAll(actor->model, object->alpha);
    func_ov001_020809f8(&actor->animFlags, object->blendIndex, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(object)) {
        ActorSlot_SetFlag8ByIndex(object->actorId, 1);
        ApplyRecordTableEntry5(object->actorId, 0, 0);
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, 0);
    }
}
