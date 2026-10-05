#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct EntryGroupDesc {
    void *source;
    s32 countA;
    s32 countB;
    s32 flags;
    s32 pad_10;
} EntryGroupDesc;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[9];
    s16 entryGroup;
} FieldObjectDef;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    void *entry;
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
    u8 pad_54[4];
    s32 visible;
    u8 pad_5c[0x44];
    u8 dataBuffers[0x18];
    void *dataBuffer;
} FieldObject;

typedef struct ContactHandler {
    void (*callback)(void);
    FieldObject *owner;
} ContactHandler;

typedef struct CollisionShape {
    u32 kind;
    u8 box[0x18];
    s32 shapeType;
    VecFx32 delta;
    u8 sweptBox[0x18];
} CollisionShape;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
    u8 pad_082[0x97];
    u8 contactEnabled;
    u8 pad_11a[0x16];
    CollisionShape shape;
    u8 pad_174[0x10];
    ContactHandler handler;
} FieldActor;

extern BOOL func_ov001_020807b4(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void SetActorExtraPosition(int index, int a1, int a2);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern u16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern void Obj_AllocDataBuffers(void *buffers, int count, int a2, int a3, int a4);
extern void TryLaunchHitEffect(void);
extern const VecFx32 data_0205344c;
extern void (*gCollisionBoundsDispatch[])(CollisionShape *shape, void *box);
extern char sOv001_BaEfDbhit_0209f188[];

void RespawnContactFieldObject(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;
    ContactHandler handler;
    EntryGroupDesc desc;
    CollisionShape *collision;

    func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    Obj_SetPosition(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    actor->contactEnabled = 1;
    handler.callback = TryLaunchHitEffect;
    handler.owner = object;
    actor->handler = handler;
    actor->shape.delta = data_0205344c;
    collision = &actor->shape;
    gCollisionBoundsDispatch[actor->shape.shapeType](collision, collision->box);
    OffsetBoxByDelta(actor->shape.box, actor->shape.sweptBox, &actor->shape.delta);
    SetActorExtraPosition(object->actorId, 0, 0x12);
    RebindAnimTracks(&actor->animFlags, object->blendIndex, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(object)) {
        ApplyRecordTableEntry5(object->actorId, 0, 0);
        if (object->visible == 0) {
            ActorSlot_SetFlag8ByIndex(object->actorId, 0);
        }
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, 0);
    }
    if (def->entryGroup == -1) {
        ZeroBytes0x14(&desc);
        desc.countA = 1;
        desc.countB = 1;
        desc.flags = 0;
        desc.source = sOv001_BaEfDbhit_0209f188;
        def->entryGroup = func_ov021_020a89c8(&desc);
    }
    if (object->dataBuffer == NULL) {
        Obj_AllocDataBuffers(object->dataBuffers, 8, 1, 1, 0);
    }
}
