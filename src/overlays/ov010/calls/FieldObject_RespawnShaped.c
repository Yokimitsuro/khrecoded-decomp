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
    u8 pad_50[3];
    s8 blendIndex;
} FieldObject;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
    u8 pad_82[0x8a];
    u8 quadNode[4];
} FieldActor;

typedef struct World {
    u8 pad_00[4];
    void **quadTree;
} World;

extern BOOL func_ov001_020807b4(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern void Obj_SetWord1CC(void *entry, void *callback);
extern void Actor_UpdateQuadTreeLink(void);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern World *GetActorRegistry(void);
extern void QuadTree_RemoveObject(void *tree, void *node);

void FieldObject_RespawnShaped(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;

    func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    Obj_SetWord1CC(object->entry, Actor_UpdateQuadTreeLink);
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
        QuadTree_RemoveObject(*GetActorRegistry()->quadTree, actor->quadNode);
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
    }
}
