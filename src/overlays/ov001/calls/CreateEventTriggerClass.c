#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectDesc {
    s16 actorKind;
    s8 unk_02;
    s8 unk_03;
    s8 shapeKind;
    u8 pad_05[0x3];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    u32 unk_14;
    s8 unk_18;
} FieldObjectDesc;

typedef struct FieldObjectClass {
    FieldObjectHook hooks[17];
    u8 pad_44[0x8];
    u32 unk_4C;
    s32 unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xA];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 isActive;
    u8 pad_7E[0x4];
    s8 unk_82;
    u8 pad_83[0xA];
    s8 unk_8D;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void RestoreFieldObjectActor();
extern void func_ov001_0207f210();
extern void ReleaseOwnerResource();
extern void func_ov001_0207f26c();
extern void GetFieldOffset40_02081258();
extern void FieldObject_MoveWithAnchor();
extern void FieldObject_TryStartEvent();
extern void GetFieldOffset78();
extern void func_ov001_02080ffc();

FieldObjectClass *CreateEventTriggerClass(int count, const FieldObjectDesc *desc)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x90, 0x84, count);

    objectClass->unk_8D = desc->unk_02;
    objectClass->unk_50 = desc->unk_03;
    objectClass->shapeKind = desc->shapeKind;
    objectClass->sizeX = desc->sizeX;
    objectClass->sizeY = desc->sizeY;
    objectClass->sizeZ = desc->sizeZ;
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_4C = desc->unk_14;
    objectClass->unk_82 = desc->unk_18;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = objectClass->actorKind >= 0 ? RestoreFieldObjectActor : NULL;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = NULL;
    objectClass->hooks[10] = GetFieldOffset40_02081258;
    objectClass->hooks[9] = FieldObject_MoveWithAnchor;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = FieldObject_TryStartEvent;
    objectClass->hooks[13] = GetFieldOffset78;
    objectClass->hooks[16] = func_ov001_02080ffc;
    objectClass->isActive = TRUE;
    return objectClass;
}
