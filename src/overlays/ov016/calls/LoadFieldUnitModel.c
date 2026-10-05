#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ShapeBoundsFunc)(struct CollisionShape *shape, s32 *bounds);

typedef struct AnimState {
    u16 flags;
} AnimState;

typedef struct FieldActor {
    u32 flags;
    AnimState anim;
    u8 pad_06[0x80 - 0x6];
    u16 rotation;
    u8 pad_82[0x10c - 0x82];
    u8 node[0xd];
    u8 nodeActive;
    u8 pad_11a[0x130 - 0x11a];
    CollisionShape shape;
    VecFx32 velocity;
    s32 sweptBounds[6];
} FieldActor;

typedef struct ActorSlot {
    u8 pad_00[0x8];
    u16 flags;
} ActorSlot;

typedef struct GroupDesc {
    const void *source;
    int count;
    int stride;
    int flags;
    int reserved;
} GroupDesc;

typedef struct FieldUnit {
    u8 pad_00[0x59];
    u8 group;
    u8 pad_5a[0x60 - 0x5a];
    void *models[21];
    s16 groupId;
    u8 pad_b6[0xc8 - 0xb6];
    u16 slotCount : 5;
    u16 soundQueued : 1;
    u16 slotFlags : 10;
} FieldUnit;

typedef struct FieldObject {
    u8 pad_00[0x4];
    FieldUnit *owner;
    void *handle;
    u8 pad_0c[0x30 - 0xc];
    u16 stateFlags;
    u8 actorId;
    u8 slotIndex;
    u8 pad_34[0x38 - 0x34];
    VecFx32 position;
    u8 pad_44[0x3];
    s8 pose;
    u8 pad_48[0x70 - 0x48];
    u16 unk_70_lo : 5;
    u16 loaded : 1;
    u16 unk_70_b6 : 1;
    u16 facing : 2;
    u16 unk_70_mid : 5;
    u16 tall : 1;
    u16 unk_70_hi : 1;
    u8 pad_72[0x77 - 0x72];
    u8 kind;
    u8 pad_78[0xbc - 0x78];
    u8 unk_bc_lo : 4;
    u8 height : 4;
    u8 unk_bd_lo : 4;
    u8 mode : 4;
    u8 pad_be[0xc0 - 0xbe];
    u32 flags;
} FieldObject;

extern const u8 sOv016_BaEfDbhit_020a6ec8[];
extern const VecFx32 data_0205344c;
extern ShapeBoundsFunc gCollisionBoundsDispatch[];
extern void QueueSoundCommandForArc(u32 seqArcNo, u32 unused2, u32 unused3, u32 commandArg);
extern void ZeroBytes0x14(void *obj);
extern s16 func_ov021_020a89c8(GroupDesc *desc);
extern void CreateFieldModelObject(void **out, u16 *counter, int arg);
extern void func_ov001_020807b4(void *handle, int group, int slot, int actorId, void *work, int mode, fx32 width, fx32 height, fx32 depth, int a, int b, int c);
extern void ApplyRecordTableEntry2(int index, u16 *counter, int arg, int kind);
extern FieldActor *ActorRegistry_GetEntityByIndex(int actorId);
extern void RebindAnimTracks(AnimState *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(AnimState *anim);
extern void SetFieldUnitPosition(FieldObject *object, const VecFx32 *position);
extern void ApplyRecordTableEntry5(int index, int param2, int param3);
extern void IndexedBytes_SetAt10(void *node, int index, int value);
extern void OffsetBoxByDelta(s32 *src, s32 *dst, VecFx32 *delta);
extern void SetActorExtraPosition(int actorId, FieldObject *object, int value);
extern void InstallFieldObjectHitCallbacks(FieldObject *object);
extern ActorSlot *ActorSlot_GetByIndex(int actorId);
extern BOOL IsNodeFlagBitClear(FieldObject *object);
extern void func_ov016_020a2688(FieldObject *object, BOOL enabled);
extern void func_ov001_0207f078(u32 bit);

static inline void UpdateShapeBounds(CollisionShape *shape)
{
    gCollisionBoundsDispatch[shape->kind](shape, (s32 *)(&shape->data + 1));
}

void LoadFieldUnitModel(FieldObject *object, int index, u16 *counter, int arg)
{
    u8 work[0x14];
    GroupDesc desc;
    void *model;
    FieldUnit *unit;
    int kind;
    fx32 width;
    FieldActor *actor;

    unit = object->owner;
    kind = object->kind;
    if (index == 4) {
        return;
    }
    if (!unit->soundQueued && object->mode >= 5) {
        QueueSoundCommandForArc(0xf8, index, (u32)counter, arg);
        unit->soundQueued = 1;
    }
    if (unit->groupId == -1) {
        ZeroBytes0x14(&desc);
        desc.count = 1;
        desc.stride = 1;
        desc.flags = 0;
        desc.source = sOv016_BaEfDbhit_020a6ec8;
        unit->groupId = func_ov021_020a89c8(&desc);
    }
    if (index < 21) {
        model = unit->models[index];
        if (model == NULL) {
            CreateFieldModelObject(&model, counter, arg);
            unit->models[index] = model;
        }
    }
    if (index == kind) {
        width = 0x1800;
        if ((index == 13 || index == 15) && object->pose == 0) {
            object->pose = 1;
        }
        if (kind == 3) {
            width = 0x1333;
        }
        if (object->tall) {
            func_ov001_020807b4(object->handle, object->owner->group, object->slotIndex, object->actorId, work, 3, 0x1800, object->height * 0x1800, 0x1800, 0, 1, 0);
        } else {
            func_ov001_020807b4(object->handle, object->owner->group, object->slotIndex, object->actorId, work, 3, width, 0x1800, width, 0, 1, 0);
        }
        ApplyRecordTableEntry2(object->actorId, counter, arg, 4);
        (*counter)++;
        actor = ActorRegistry_GetEntityByIndex(object->actorId);
        RebindAnimTracks(&actor->anim, object->pose, 0);
        Flags16_ClearBit1(&actor->anim);
        SetFieldUnitPosition(object, &object->position);
        if (object->kind == 6) {
            int rotation = ((object->facing + 2) & 3) << 14;

            if (!(actor->flags & 0x20)) {
                actor->rotation = rotation;
                actor->anim.flags |= 0x20;
            }
        } else if (!(actor->flags & 0x20)) {
            actor->rotation = 0;
            actor->anim.flags |= 0x20;
        }
        ApplyRecordTableEntry5(object->actorId, 0, 0);
        IndexedBytes_SetAt10(actor->node, 1, 4);
        object->stateFlags |= 4;
        object->flags |= 0x2000000;
        actor->nodeActive = 1;
        actor->velocity = data_0205344c;
        UpdateShapeBounds(&actor->shape);
        OffsetBoxByDelta(actor->shape.bounds, actor->sweptBounds, &actor->velocity);
        SetActorExtraPosition(object->actorId, object, 0x1e);
        InstallFieldObjectHitCallbacks(object);
        ActorSlot_GetByIndex(object->actorId)->flags |= 0x200;
        object->loaded = 1;
        func_ov016_020a2688(object, IsNodeFlagBitClear(object));
        IndexedBytes_SetAt10(actor->node, 3, 0xc);
        func_ov001_0207f078(0xc);
    }
}
