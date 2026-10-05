#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

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

typedef struct ModelTransform {
    u8 pad_00[0xb0];
    VecFx32 scale;
} ModelTransform;

typedef struct ModelEntry {
    u8 pad_00[0x08];
    u16 flags;
    u8 pad_0a[0x0a];
    ModelTransform transform;
} ModelEntry;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ModelEntry *entry;
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
} FieldObject;

typedef struct ScaleTuning {
    u8 pad_00[0x14];
    s16 heightScaleRate;
} ScaleTuning;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
} FieldActor;

extern BOOL func_ov001_020807b4(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void func_ov042_020bd110(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern ScaleTuning data_020536c0;

void RespawnScaledFieldObject(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;
    ModelTransform *transform;
    fx32 scale;

    func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    func_ov042_020bd110();
    scale = FX_Mul(-object->position.z, data_020536c0.heightScaleRate) + FX32_ONE;
    transform = &object->entry->transform;
    transform->scale.z = scale;
    transform->scale.y = transform->scale.z;
    transform->scale.x = transform->scale.y;
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    Obj_SetPosition(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks(&actor->animFlags, object->blendIndex, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(object)) {
        ActorSlot_SetFlag8ByIndex(object->actorId, TRUE);
        ApplyRecordTableEntry5(object->actorId, 0, 0);
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
    }
    object->entry->flags |= 0x200;
}
