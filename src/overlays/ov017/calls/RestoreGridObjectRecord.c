#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridManager {
    u8 pad_00[0x59];
    u8 listId;
} GridManager;

typedef struct GridActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 animFrame;
    u8 pad_82[0x8a];
    u8 collision[4];
} GridActor;

typedef struct GridObject {
    u8 pad_00[4];
    GridManager *manager;
    void *node;
    u8 pad_0C[0x24];
    u16 statusFlags;
    u8 slot;
    u8 group;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 idleAnim;
    u8 pad_48;
    s8 cellsX;
    s8 cellsY;
    s8 cellsZ;
} GridObject;

typedef struct ShapeBuffer {
    u8 data[20];
} ShapeBuffer;

extern void func_ov001_020807b4(void *node, int listId, int group, int slot, ShapeBuffer *shape, int kind, fx32 sizeX,
                                fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mask);
extern void ApplyRecordTableEntry2(int slot, u16 *counter, int arg, int mode);
extern GridActor *ActorRegistry_GetEntityByIndex(int slot);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsNodeFlagBitClear(GridObject *object);
extern void ApplyRecordTableEntry5(int slot, int a, int b);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void IndexedBytes_SetAt10(void *collision, int layer, int mask);
extern void func_ov001_0207f078(int mask);
extern void SetActorExtraPosition(int slot, GridObject *object, int offset);

void RestoreGridObjectRecord(GridObject *object, int phase, u16 *counter, int arg)
{
    ShapeBuffer shape;
    GridActor *actor;

    if (phase != 2) {
        return;
    }
    func_ov001_020807b4(object->node, object->manager->listId, object->group, object->slot, &shape, 3,
                        object->cellsX * 0x1800, object->cellsY * 0x1800, object->cellsZ * 0x1800, 0, TRUE, 0);
    ApplyRecordTableEntry2(object->slot, counter, arg, 4);
    (*counter)++;
    actor = ActorRegistry_GetEntityByIndex(object->slot);
    Obj_SetPosition(actor, &object->position);
    if (!(actor->flags & 0x20)) {
        actor->animFrame = 0;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks(&actor->animFlags, object->idleAnim, 0);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsNodeFlagBitClear(object)) {
        ApplyRecordTableEntry5(object->slot, 0, 0);
    }
    ActorSlot_SetFlag8ByIndex(object->slot, IsNodeFlagBitClear(object));
    IndexedBytes_SetAt10(actor->collision, 1, 4);
    IndexedBytes_SetAt10(actor->collision, 3, 0xe);
    func_ov001_0207f078(0xe);
    SetActorExtraPosition(object->slot, object, 0x1c);
    object->statusFlags |= 4;
}
