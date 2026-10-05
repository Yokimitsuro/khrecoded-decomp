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
} FieldObjectClass;

typedef struct {
    s16 actorKind;
    s8 variant;
} FieldObjectKindDesc;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void RespawnScaledFieldObject();
extern void func_ov001_0207f210();
extern void ReleaseOwnerResource();
extern void func_ov001_0207f26c();
extern void func_ov001_02086088();
extern void func_ov001_0208608c();
extern void SetPanelPosition();
extern void func_ov001_020860cc();
extern void func_ov001_020860d4();
extern void DrawObjectWithDepthScale();

FieldObjectClass *CreateFieldObjectClassType16(int count, const FieldObjectKindDesc *desc)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x88, 0x58, count);

    objectClass->variant = desc->variant;
    objectClass->param = 0x10;
    objectClass->shapeKind = -1;
    objectClass->values[0] = 0;
    objectClass->values[1] = 0;
    objectClass->values[2] = 0;
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnScaledFieldObject;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_02086088;
    objectClass->hooks[10] = func_ov001_0208608c;
    objectClass->hooks[9] = SetPanelPosition;
    objectClass->hooks[11] = func_ov001_020860cc;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov001_020860d4;
    objectClass->hooks[13] = NULL;
    objectClass->hooks[15] = DrawObjectWithDepthScale;
    objectClass->classType = 0x10;
    return objectClass;
}
