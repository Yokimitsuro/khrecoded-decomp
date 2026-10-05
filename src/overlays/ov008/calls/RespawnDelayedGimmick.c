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

typedef struct Gimmick {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    void *entry;
    u8 pad_10[0x4];
    int (*update)(struct Gimmick *gimmick);
    u8 pad_18[0x20];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x03];
    s8 blendIndex;
    u8 pad_54[0x4];
    int phase;
    fx32 delay;
    fx32 timer;
} Gimmick;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
} FieldActor;

extern BOOL func_ov001_020807b4(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(Gimmick *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern int Gimmick_WaitOpenDelay(Gimmick *gimmick);

void RespawnDelayedGimmick(Gimmick *gimmick)
{
    FieldObjectDef *def = gimmick->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;

    func_ov001_020807b4(gimmick->entry, gimmick->group, gimmick->index, gimmick->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, gimmick->angle, !(gimmick->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(gimmick->actorId, def->recordParamA, def->recordParamB, 3);
    actor = ActorRegistry_GetEntityByIndex(gimmick->actorId);
    Obj_SetPosition(actor, &gimmick->position);
    angle = gimmick->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    gimmick->update = Gimmick_WaitOpenDelay;
    gimmick->phase = 0;
    gimmick->timer = -gimmick->delay;
    RebindAnimTracks(&actor->animFlags, gimmick->blendIndex, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(gimmick)) {
        ApplyRecordTableEntry5(gimmick->actorId, 0, 0);
        ActorSlot_SetFlag8ByIndex(gimmick->actorId, FALSE);
    } else {
        ActorSlot_SetFlag8ByIndex(gimmick->actorId, FALSE);
    }
}
