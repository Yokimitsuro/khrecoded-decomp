#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct {
    u8 pad_00[0x54];
    u16 *useCount;
    void *animData;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[7];
    s8 group;
    s8 index;
    u8 pad_86[2];
    s16 modelIds[4];
    fx32 baseHeight;
    s8 stopIndex;
} ElevatorWork;

typedef struct {
    u8 pad_00[8];
    ElevatorWork *work;
    void *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[5];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u8 pad_50[3];
    s8 state;
    u8 pad_54[0x10];
    void *record;
    fx32 frame;
    s8 cooldown;
    u8 isStatic : 1;
    s8 load;
    s8 count;
    s16 timer;
} ElevatorObject;

typedef struct {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
} FieldActor;

extern void func_ov001_020807b4(void *entry, u8 group, u8 index, u8 actorId, ShapeParams *shapeOut, int shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, u16 angle, BOOL visible, BOOL solid);
extern void ApplyRecordTableEntry2(int index, void *a1, void *a2, int mode);
extern u16 FieldObject_GetSavedValue(ElevatorObject *object);
extern u32 ObjectManager_GetSecondEntryParam(int id);
extern u32 ObjectManager_GetFirstEntryParam(int id);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void *SND_RegisterSeq(u32 fileId, u32 heapId);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(FieldActor *actor, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(ElevatorObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void SetActorExtraPosition(u32 id, void *source, int mask);
extern void *func_ov001_0207f060(int group, int index);
extern VecFx32 *func_ov001_0207f838(void *object);
extern void CallFieldObjectHook24(void *object, VecFx32 *position);
extern void BuildDescendingLevelTable(ElevatorWork *work, ElevatorObject *object);
extern void QueueSoundCommandForArc(int command);

void RespawnElevatorObject(ElevatorObject *object)
{
    ElevatorWork *work = object->work;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;

    if (object->isStatic) {
        func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, work->shapeKind, work->sizeX, work->sizeY, work->sizeZ, object->angle, !(object->flags & 8), TRUE);
        ApplyRecordTableEntry2(object->actorId, work->useCount, work->animData, 3);
        if (!(FieldObject_GetSavedValue(object) & 1)) {
            object->state = 1;
            object->flags |= 0x20;
        }
    } else {
        void *block;

        (*work->useCount)--;
        func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, -1, work->sizeX, work->sizeY, work->sizeZ, object->angle, !(object->flags & 8), TRUE);
        block = func_0202c4a0(ObjectManager_GetSecondEntryParam(work->modelIds[object->index - 1]), 3);
        object->record = SND_RegisterSeq(ObjectManager_GetFirstEntryParam(work->modelIds[object->index - 1]), 3);
        ApplyRecordTableEntry2(object->actorId, object->record, block, 3);
        NNSi_FndFreeFromDefaultHeap(block);
        if (!(FieldObject_GetSavedValue(object) & 1)) {
            object->state = 0;
            object->flags |= 0x10;
            object->load = 6;
            object->cooldown = 0;
            object->count = 0;
            object->timer = 0;
        }
    }
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    Obj_SetPosition(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks(&actor->animFlags, object->state, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(object)) {
        ActorSlot_SetFlag8ByIndex(object->actorId, TRUE);
        ApplyRecordTableEntry5(object->actorId, 0, 0);
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
    }
    SetActorExtraPosition(object->actorId, NULL, 0x24);
    if (object->isStatic) {
        if (work->baseHeight < 0) {
            work->baseHeight = func_ov001_0207f838(func_ov001_0207f060(work->group, work->index))->y;
        }
        if (!(FieldObject_GetSavedValue(object) & 1)) {
            VecFx32 position;

            work->stopIndex = 0;
            position = *func_ov001_0207f838(func_ov001_0207f060(work->group, work->index));
            position.y = work->baseHeight;
            CallFieldObjectHook24(func_ov001_0207f060(work->group, work->index), &position);
        }
        BuildDescendingLevelTable(work, object);
        QueueSoundCommandForArc(0x19e);
    }
}

