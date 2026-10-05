#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TriggerLink {
    u8 kind;
    u8 pad_01;
    u16 arg;
    struct TriggerLink *partner;
} TriggerLink;

typedef struct FieldObjectClass {
    u8 pad_00[0x59];
    u8 modelKind;
    u8 pad_5A[0x12];
    u8 sharedModel[0x78];
    void *sharedResource;
    u8 pad_E8[0x88];
    s16 effectBank;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldObjectClass *objClass;
    void *model;
    u8 pad_0C[0x24];
    u16 renderFlags;
    u8 actorId;
    u8 paletteId;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    u8 pad_48[2];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[4];
    s32 kind : 16;
    s32 subKind : 12;
    s32 pad_bits : 4;
    u8 pad_54[0xc];
    TriggerLink *trigger;
} FieldObject;

typedef void (*ShapeBoundsFunc)(void *shape, void *bounds);

typedef struct ContactCallback {
    void *func;
    FieldObject *object;
} ContactCallback;

typedef struct Actor {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x5a];
    u8 jointBlend[0x30];
    u8 collision[0xd];
    u8 sweepEnabled;
    u8 pad_11A[0x16];
    u8 shape[4];
    u8 bounds[0x18];
    s32 shapeType;
    VecFx32 sweepDelta;
    u8 sweptBounds[0x30];
    ContactCallback contactCallback;
} Actor;

typedef struct EffectDesc {
    void *data;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} EffectDesc;

extern const VecFx32 data_0205344c;
extern ShapeBoundsFunc gCollisionBoundsDispatch[];
extern u8 sOv017_BaEfDbhit_020a5f38[];

extern void func_ov001_020807b4(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern int IsNodeFlagBitClear(FieldObject *obj);
extern void ApplyRecordTableEntry2(int index, u16 *counter, int arg, int count);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(void *target, int value, int extra);
extern void Flags16_ClearBit1(void *target);
extern void selectJointAnimationBlend(void *target, int blend, void *joints, int frame);
extern void Obj_SetPosition(Actor *actor, const VecFx32 *position);
extern void ApplyRecordTableEntry5(int index, int a, int b);
extern void IndexedBytes_SetAt10(void *target, int a, int b);
extern void func_ov001_0207f078(u32 bit);
extern int IsFieldFlagBit1Set(FieldObject *obj);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void SetActorExtraPosition(u32 id, FieldObject *obj, int value);
extern void FieldObject_HandleContact_020a33d8();
extern void func_ov017_020a3c98(FieldObject *obj, int arg);
extern void func_0202edb0(void *object, u16 *counter, int arg, int count);
extern void ZeroBytes0x14(void *obj);
extern s16 func_ov021_020a89c8(EffectDesc *desc);

static inline BOOL IsState1Or2(FieldObject *obj)
{
    BOOL result = TRUE;
    if (obj->state != 2 && obj->state != 1) {
        result = FALSE;
    }
    return result;
}

static inline void LoadObjectModel(FieldObject *obj, u8 *buffer, int mode, fx32 scale, fx32 height)
{
    func_ov001_020807b4(obj->model, obj->objClass->modelKind, obj->paletteId, obj->actorId, buffer, mode, scale, height, scale, 0, 1, 0);
}

void LoadTriggerObjectPhase(FieldObject *obj, int phase, u16 *counter, int arg)
{
    FieldObjectClass *objClass = *(FieldObjectClass **)((u8 *)obj + 4);
    u8 buffer[20];
    Actor *actor;
    BOOL enable;
    BOOL canEnable;
    ContactCallback callback;
    EffectDesc desc;
    TriggerLink *trigger;
    int subKind;
    u8 *shape;
    fx32 scale;

    if (phase == obj->kind) {
        if (obj->flags & 1) {
            scale = obj->kind == 3 ? 0x1333 : 0x1800;
            LoadObjectModel(obj, buffer, 3, scale, 0x1800);
        } else {
            if (IsState1Or2(obj)) {
                return;
            }
            if (!IsNodeFlagBitClear(obj)) {
                return;
            }
            LoadObjectModel(obj, buffer, -1, 0, 0);
        }
        ApplyRecordTableEntry2(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        RebindAnimTracks(&actor->drawFlags, obj->animIndex, 0);
        Flags16_ClearBit1(&actor->drawFlags);
        selectJointAnimationBlend(&actor->drawFlags, 2, actor->jointBlend, -1);
        Obj_SetPosition(actor, &obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        enable = FALSE;
        ApplyRecordTableEntry5(obj->actorId, 0, 0);
        IndexedBytes_SetAt10(actor->collision, 1, 4);
        IndexedBytes_SetAt10(actor->collision, 3, 0xe);
        func_ov001_0207f078(0xe);
        canEnable = FALSE;
        if (!IsFieldFlagBit1Set(obj) && !IsState1Or2(obj)) {
            canEnable = TRUE;
        }
        if (canEnable && IsNodeFlagBitClear(obj)) {
            enable = TRUE;
        }
        ActorSlot_SetFlag8ByIndex(obj->actorId, enable);
        obj->renderFlags |= 4;
        if (obj->flags & 1) {
            actor->sweepEnabled = 1;
            actor->sweepDelta = data_0205344c;
            shape = actor->shape;
            gCollisionBoundsDispatch[actor->shapeType](shape, shape + 4);
            OffsetBoxByDelta(actor->bounds, actor->sweptBounds, &actor->sweepDelta);
        }
        SetActorExtraPosition(obj->actorId, obj, 8);
        callback.func = FieldObject_HandleContact_020a33d8;
        callback.object = obj;
        actor->contactCallback = callback;
        subKind = obj->subKind;
        if (subKind == 1 || subKind == 2 || ((trigger = obj->trigger) != NULL && trigger->kind == 3 && (trigger->partner == trigger || trigger->partner == NULL))) {
            func_ov017_020a3c98(obj, 1);
            return;
        }
    } else if (phase == 8) {
        if (objClass->sharedResource == NULL) {
            func_0202edb0(objClass->sharedModel, counter, arg, 4);
            RebindAnimTracks(objClass->sharedModel, 0, 0);
            (*counter)++;
            ZeroBytes0x14(&desc);
            desc.unk_04 = 1;
            desc.unk_08 = 1;
            desc.unk_0C = 0;
            desc.data = sOv017_BaEfDbhit_020a5f38;
            objClass->effectBank = func_ov021_020a89c8(&desc);
        }
    }
}

