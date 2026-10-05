#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ObjectClass {
    u8 pad_00[0x54];
    s32 drawParamA;
    s32 drawParamB;
    u8 pad_5c[0x14];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    s8 kind;
    u8 pad_7d[7];
    s32 loaded;
    u8 animState[0xd8];
    u8 blendTable[4];
} ObjectClass;

typedef struct ActorBody {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 rotation;
    u8 pad_82[0x8a];
    u8 collision[4];
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    void *model;
    u8 pad_10[0x28];
    u8 actorId;
    u8 slotX;
    u8 slotY;
    u8 pad_3b[5];
    VecFx32 position;
    u16 rotation;
    u16 flags;
    u8 pad_50[3];
    s8 animTrack;
} FieldObject;

extern void FieldGroup_ShufflePositions(ObjectClass *objectClass);
extern u32 func_ov001_0207ee3c(int index);
extern u32 func_ov001_0207ee70(int index);
extern void *SND_RegisterSeq(int a, int b);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void func_0202edb0(void *animState, void *record, void *block, int count);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void selectJointAnimationBlend(void *animState, int trackIndex, void *blendTable, int blendIndex);
extern void func_ov001_020807b4(void *model, int slotX, int slotY, int actorId, void *work, int kind,
                                fx32 scaleX, fx32 scaleY, fx32 scaleZ, int rotation, BOOL visible, int arg);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern ActorBody *ActorRegistry_GetEntityByIndex(int actorId);
extern void Obj_SetPosition(ActorBody *actor, const VecFx32 *position);
extern void func_ov001_020809f8(u16 *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(u16 *anim);
extern BOOL func_ov001_0207f7cc(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int param2, int param3);
extern void IndexedBytes_SetAt10(void *collision, int a, int b);

static inline void Actor_InitRotation(ActorBody *actor, u16 rotation)
{
    if ((actor->flags & 0x20) == 0) {
        actor->rotation = rotation;
        actor->animFlags |= 0x20;
    }
}

void FieldObject_LoadAndPlace(FieldObject *object)
{
    ObjectClass *objectClass = object->objectClass;
    ActorBody *actor;
    u8 work[0x14];

    if (objectClass->loaded == 0) {
        void *record;
        void *block;
        objectClass->loaded = 1;
        FieldGroup_ShufflePositions(objectClass);
        record = SND_RegisterSeq(func_ov001_0207ee3c(0xcb), 3);
        block = func_0202c4a0(func_ov001_0207ee70(0xcb), 3);
        func_0202edb0(objectClass->animState, record, block, 3);
        NNSi_FndFreeFromDefaultHeap(block);
        selectJointAnimationBlend(objectClass->animState, 0, objectClass->blendTable, 0);
        selectJointAnimationBlend(objectClass->animState, 2, objectClass->blendTable, 0);
    }
    func_ov001_020807b4(object->model, object->slotX, object->slotY, object->actorId, work, objectClass->kind,
                        objectClass->scaleX, objectClass->scaleY, objectClass->scaleZ, object->rotation,
                        (object->flags & 8) == 0, 1);
    ApplyRecordTableEntry2(object->actorId, objectClass->drawParamA, objectClass->drawParamB, 3);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    Obj_SetPosition(actor, &object->position);
    Actor_InitRotation(actor, object->rotation);
    func_ov001_020809f8(&actor->animFlags, object->animTrack, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (func_ov001_0207f7cc(object)) {
        ActorSlot_SetFlag8ByIndex(object->actorId, TRUE);
        ApplyRecordTableEntry5(object->actorId, 0, 0);
        IndexedBytes_SetAt10(actor->collision, 1, 4);
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
    }
}
