#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    s32 scale;
    s32 unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    u8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void func_ov001_02083758();
extern void func_ov001_0207f210();
extern void ResetPatrolObject();
extern void FreeLoaderBuffers();
extern void FieldObject_ResetToRandomPoint();
extern void GetFieldOffset40_02083c28();
extern void SetActorTargetPosition();
extern void GetWorkFieldOffset50_02083c54();
extern void func_ov001_020846b8();
extern void func_ov001_02083c5c();
extern void GetFieldOffset40_020847bc();
extern void DrawActorWithShadow();

FieldObjectClass *CreateFieldObjectClassType9(int count)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x84, 0x1bc, count);

    objectClass->unk_50 = 0;
    objectClass->shapeKind = 2;
    objectClass->unk_70 = 0x266;
    objectClass->unk_74 = 0;
    objectClass->unk_78 = 0;
    objectClass->actorKind = 0x7b;
    objectClass->unk_82 = 2;
    objectClass->scale = 0x2000;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = func_ov001_02083758;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ResetPatrolObject;
    objectClass->hooks[6] = FreeLoaderBuffers;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = FieldObject_ResetToRandomPoint;
    objectClass->hooks[10] = GetFieldOffset40_02083c28;
    objectClass->hooks[9] = SetActorTargetPosition;
    objectClass->hooks[11] = GetWorkFieldOffset50_02083c54;
    objectClass->hooks[14] = func_ov001_020846b8;
    objectClass->hooks[12] = func_ov001_02083c5c;
    objectClass->hooks[13] = GetFieldOffset40_020847bc;
    objectClass->hooks[15] = DrawActorWithShadow;
    objectClass->classType = 9;
    return objectClass;
}
