#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    s32 scale;
    s32 param;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    s32 values[3];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83;
    s8 variant;
    s8 slotIndex;
} FieldObjectClass;

typedef struct FieldObjectDesc {
    s32 param;
    s16 actorKind;
    s8 variant;
    s8 shapeKind;
    s32 values[3];
} FieldObjectDesc;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void FieldObject_SpawnActor();
extern void func_ov001_0207f210();
extern void ReleaseOwnerResource();
extern void func_ov001_0207f26c();
extern void func_ov001_02080ba8();
extern void GetFieldOffset40();
extern void FieldObject_SetPosition();
extern void GetWorkFieldOffset50();
extern void DispatchShapePairTest();

FieldObjectClass *CreateFieldObjectClassFromDesc(int count, const FieldObjectDesc *desc)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x88, 0x5c, count);

    objectClass->variant = desc->variant;
    objectClass->slotIndex = -1;
    objectClass->param = desc->param;
    objectClass->shapeKind = desc->shapeKind;
    objectClass->values[0] = desc->values[0];
    objectClass->values[1] = desc->values[1];
    objectClass->values[2] = desc->values[2];
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = FieldObject_SpawnActor;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_02080ba8;
    objectClass->hooks[10] = GetFieldOffset40;
    objectClass->hooks[9] = FieldObject_SetPosition;
    objectClass->hooks[11] = GetWorkFieldOffset50;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = DispatchShapePairTest;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 0;
    return objectClass;
}
