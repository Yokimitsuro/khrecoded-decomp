#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldEntry {
    u8 pad_00[8];
    u16 flags;
} FieldEntry;

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
    FieldEntry *entry;
    u8 pad_10[4];
    void *stateHandler;
    u8 pad_18[0x20];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[3];
    s8 blendIndex;
    u8 pad_54[4];
    int state;
} FieldObject;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0xa2];
    VecFx32 position;
} FieldActor;

extern BOOL func_ov001_020807b4(FieldEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void func_ov010_020a0b10(void);

void FieldObject_RespawnIdle(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;

    func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    object->stateHandler = func_ov010_020a0b10;
    object->state = 0;
    ActorRegistry_GetEntityByIndex(object->actorId);
    if (IsObjectFlagClear(object)) {
        ApplyRecordTableEntry5(object->actorId, 0, 0);
    }
    ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
}
