#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneNode {
    u8 pad_00[0x74];
    s32 loaded;
    u8 pad_78[0x38];
    VecFx32 scale;
    u8 pad_bc[0x48];
} SceneNode;

typedef struct ObjectDef {
    u8 pad_000[0x59];
    u8 modelKind;
    u8 pad_05a[6];
    SceneNode nodes[4];
    s16 effectBank;
} ObjectDef;

typedef struct EntryGroupDesc {
    const void *data;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
} EntryGroupDesc;

typedef struct CollisionShape {
    u8 *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

typedef struct HitCallback {
    void *func;
    void *context;
} HitCallback;

typedef struct Actor {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x32];
    VecFx32 scale;
    u8 pad_c0[0x4c];
    u8 collision[0xd];
    u8 falling;
    u8 pad_11a[0x16];
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
    u8 pad_174[0x10];
    HitCallback hitHandlers[2];
} Actor;

typedef struct FieldObject {
    u8 pad_00[4];
    ObjectDef *def;
    void *model;
    u8 pad_0c[0x24];
    u16 renderFlags;
    u8 actorId;
    u8 paletteId;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    void *resource;
    u8 pad_4c[4];
    u16 flags;
    s8 state;
    u8 pad_53[0x4d];
    s32 kind;
} FieldObject;

extern const u8 sOv018_BaEfDbhit_020a3870[];
extern const VecFx32 data_0205344c;
extern ComputeBoundsFunc gCollisionBoundsDispatch[];

extern void ZeroBytes0x14(void *obj);
extern s16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern void func_0202edb0(void *object, u16 *counter, int arg, int count);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern BOOL IsNodeFlagBitClear(FieldObject *obj);
extern void func_ov001_020807b4(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void ApplyRecordTableEntry2(int index, u16 *counter, int arg, int count);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *target);
extern void SetScaledPosition(FieldObject *obj, const VecFx32 *position);
extern void ApplyRecordTableEntry5(int index, int a, int b);
extern void IndexedBytes_SetAt10(void *target, int a, int b);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern int func_ov001_02063a38(void);
extern void func_ov018_020a335c(FieldObject *obj, BOOL disable);
extern void SetActorExtraPosition(u32 id, FieldObject *obj, int value);
extern void FieldObject_HandleStrongHit(void);
extern void FieldObject_SpawnContactEffect(void);
extern void func_ov001_0207f078(u32 bit);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void Flags16_SetBit1(void *object);

static inline HitCallback MakeCallback(void *func, void *context)
{
    HitCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

static inline void ComputeBounds(CollisionShape *shape)
{
    gCollisionBoundsDispatch[shape->kind](shape, (s32 *)((u8 *)shape + 4));
}

void LoadKind6ObjectPhase(FieldObject *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    EntryGroupDesc desc;
    int kind = obj->kind;
    SceneNode *node = NULL;
    ObjectDef *def = obj->def;
    Actor *actor;
    BOOL enable;

    switch (phase) {
    case 3:
        if (def->nodes[0].loaded == 0) {
            node = &def->nodes[0];
            ZeroBytes0x14(&desc);
            desc.unk_04 = 1;
            desc.unk_08 = 1;
            desc.unk_0c = 0;
            desc.data = sOv018_BaEfDbhit_020a3870;
            def->effectBank = func_ov021_020a89c8(&desc);
        }
        break;
    case 1:
        if (def->nodes[1].loaded == 0) {
            node = &def->nodes[1];
        }
        break;
    case 10:
        if (def->nodes[2].loaded == 0) {
            node = &def->nodes[2];
        }
        break;
    case 2:
        if (def->nodes[3].loaded == 0) {
            node = &def->nodes[3];
        }
        break;
    }
    if (node != NULL) {
        func_0202edb0(node, counter, arg, 4);
        node->scale.z = FX_Div(0x1000, 0x1800);
        node->scale.y = node->scale.z;
        node->scale.x = node->scale.y;
    }
    if (phase == kind) {
        if (obj->flags & 1) {
            func_ov001_020807b4(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1000, 0x1000, 0x1000, 0, 1, 0);
        } else {
            if (obj->state != 0 || !IsNodeFlagBitClear(obj)) {
                return;
            }
            func_ov001_020807b4(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, -1, 0, 0, 0, 0, 1, 0);
        }
        ApplyRecordTableEntry2(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        RebindAnimTracks(&actor->drawFlags, obj->animIndex, 0);
        Flags16_ClearBit1(&actor->drawFlags);
        actor->scale.z = FX_Div(0x1000, 0x1800);
        actor->scale.y = actor->scale.z;
        actor->scale.x = actor->scale.y;
        SetScaledPosition(obj, &obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        ApplyRecordTableEntry5(obj->actorId, 0, 0);
        enable = TRUE;
        IndexedBytes_SetAt10(actor->collision, 1, 4);
        if ((obj->flags & 8) || obj->state != 0 || !IsNodeFlagBitClear(obj)) {
            enable = FALSE;
        }
        ActorSlot_SetFlag8ByIndex(obj->actorId, enable);
        obj->renderFlags |= 4;
        if (obj->flags & 1) {
            actor->falling = 1;
            actor->delta = data_0205344c;
            ComputeBounds(&actor->shape);
            OffsetBoxByDelta(actor->shape.bounds, actor->sweptBounds, &actor->delta);
        }
        if (func_ov001_02063a38() == 7) {
            func_ov018_020a335c(obj, TRUE);
        }
        SetActorExtraPosition(obj->actorId, obj, 0xd);
        switch (obj->kind) {
        case 3:
            actor->hitHandlers[1] = MakeCallback(FieldObject_SpawnContactEffect, obj);
            break;
        case 1:
            break;
        case 2:
            actor->hitHandlers[0] = MakeCallback(FieldObject_HandleStrongHit, obj);
            break;
        }
        IndexedBytes_SetAt10(actor->collision, 3, 0xc);
        func_ov001_0207f078(0xc);
    } else if (phase == 8 && obj->state == 0) {
        obj->resource = NNSi_FndAllocFromDefaultHeap(0x104);
        func_0202edb0(obj->resource, counter, arg, 4);
        RebindAnimTracks(obj->resource, 0, 0);
        Flags16_SetBit1(obj->resource);
        (*counter)++;
    }
}
