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
    u8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83;
    s32 activeCount;
    s32 unk_88;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void RespawnCapsuleFieldObject();
extern void func_ov001_0207f210();
extern void FieldObject_ReleaseWithSlotReset();
extern void func_ov001_0207f26c();
extern void SetActorRaisedCollision();
extern void GetFieldOffset40_02082bfc();
extern void FieldObject_SetActorPosition();
extern void GetWorkFieldOffset50_02082c6c();
extern void func_ov001_02082c74();

FieldObjectClass *CreateFieldObjectClassType7(int count)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x8c, 0x7c, count);

    objectClass->param = 0;
    objectClass->shapeKind = 1;
    objectClass->values[0] = 0xccd;
    objectClass->values[1] = 0x3000;
    objectClass->values[2] = 0;
    objectClass->actorKind = 0x81;
    objectClass->unk_82 = 0xff;
    objectClass->scale = 0;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnCapsuleFieldObject;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = FieldObject_ReleaseWithSlotReset;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = SetActorRaisedCollision;
    objectClass->hooks[10] = GetFieldOffset40_02082bfc;
    objectClass->hooks[9] = FieldObject_SetActorPosition;
    objectClass->hooks[11] = GetWorkFieldOffset50_02082c6c;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov001_02082c74;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 7;
    objectClass->activeCount = 0;
    objectClass->unk_88 = 0;
    return objectClass;
}
