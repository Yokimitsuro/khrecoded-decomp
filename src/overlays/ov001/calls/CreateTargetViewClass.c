#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[17];
    u8 pad_44[0x20];
    s16 actorKind;
    u8 pad_66[0x16];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    s8 unk_82;
    u8 pad_83[0x1];
    u32 projection[14];
    s8 targetIndex;
} FieldObjectClass;

typedef struct TargetViewDesc {
    int actorKind;
} TargetViewDesc;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void SpawnFieldObjectActor();
extern void func_ov001_0207f210();
extern void FieldObject_ClearMatchingTarget();
extern void func_ov001_0207f26c();
extern void SetSessionMarkerActive();
extern void GetFieldOffset40_02081be4();
extern void FieldObject_DrawTargetView();
extern void func_ov001_02081d6c();
extern void LoadDefaultProjectionValues(u32 *projection);

FieldObjectClass *CreateTargetViewClass(int count, const TargetViewDesc *desc)
{
    FieldObjectClass *objectClass = CreateByteGrid(0xc0, 0x5c, count);

    objectClass->shapeKind = -1;
    objectClass->actorKind = -1;
    objectClass->unk_82 = 0;
    objectClass->hooks[15] = FieldObject_DrawTargetView;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = FieldObject_ClearMatchingTarget;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[8] = SetSessionMarkerActive;
    objectClass->hooks[10] = GetFieldOffset40_02081be4;
    objectClass->hooks[16] = func_ov001_02081d6c;
    objectClass->classType = 3;
    objectClass->targetIndex = -1;
    objectClass->actorKind = desc->actorKind;
    if (objectClass->actorKind >= 0) {
        objectClass->hooks[2] = SpawnFieldObjectActor;
    } else {
        objectClass->hooks[2] = NULL;
    }
    LoadDefaultProjectionValues(objectClass->projection);
    return objectClass;
}
