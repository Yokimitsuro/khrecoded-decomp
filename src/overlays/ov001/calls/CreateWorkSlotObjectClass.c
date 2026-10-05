#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectDesc {
    s16 actorKind;
    s8 unk_02;
    u8 unk_03;
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
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83[0x1];
    s8 unk_84;
    u8 unk_85;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void func_ov001_0208154c();
extern void func_ov001_0207f210();
extern void ReleaseOwnerResource();
extern void func_ov001_0207f26c();
extern void func_ov001_020816a8();
extern void GetFieldOffset40_020816ac();
extern void GetFieldOffset40_020816b0();
extern void func_ov001_020816b4();

FieldObjectClass *CreateWorkSlotObjectClass(int count, const FieldObjectDesc *desc)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x88, 0x5c, count);

    objectClass->unk_84 = desc->unk_02;
    objectClass->unk_85 = desc->unk_03;
    objectClass->unk_50 = 0;
    objectClass->shapeKind = -1;
    objectClass->sizeX = 0;
    objectClass->sizeY = 0;
    objectClass->sizeZ = 0;
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 1;
    objectClass->unk_4C = 0;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = func_ov001_0208154c;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_020816a8;
    objectClass->hooks[10] = GetFieldOffset40_020816ac;
    objectClass->hooks[9] = NULL;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = NULL;
    objectClass->hooks[13] = GetFieldOffset40_020816b0;
    objectClass->hooks[5] = func_ov001_020816b4;
    objectClass->classType = 2;
    return objectClass;
}
