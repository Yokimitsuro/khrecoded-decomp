#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0x24];
    s16 actorKind;
    u8 pad_66[0x16];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    s8 unk_82;
    u8 pad_83[0x1];
    u32 projection[14];
    fx32 halfWidth;
    fx32 halfDepth;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void RespawnFieldObjectActor();
extern void func_ov001_0207f210();
extern void ReleaseOwnerResource();
extern void func_ov001_0207f26c();
extern void func_ov001_02081fac();
extern void LoadDefaultProjectionValues(u32 *projection);

FieldObjectClass *CreateProjectionViewClass(int count, u16 actorKind, fx32 width, fx32 depth)
{
    FieldObjectClass *objectClass = CreateByteGrid(0xc4, 0x58, count);

    objectClass->shapeKind = -1;
    objectClass->actorKind = actorKind;
    objectClass->unk_82 = 0;
    objectClass->hooks[15] = func_ov001_02081fac;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnFieldObjectActor;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->classType = 13;
    objectClass->halfWidth = width >> 1;
    objectClass->halfDepth = depth >> 1;
    LoadDefaultProjectionValues(objectClass->projection);
    return objectClass;
}
