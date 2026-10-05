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
    u8 pad_83[0x79];
    s32 activeCount;
} FieldObjectClass;

extern FieldObjectClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern s32 func_ov001_02063a38(void);
extern void AcquireEffectRecordPair();
extern void FieldObject_EnsureModelsLoaded();
extern void ActivateFieldSwitchObject();
extern void func_ov001_0207f210();
extern void ReleaseTaskWithCallback();
extern void func_ov001_0207f26c();
extern void ApplyRecordOrSetState();
extern void GetFieldOffset40_02082354();
extern void FieldObject_PlaceActor();
extern void FieldObject_DrawInstance();

FieldObjectClass *CreateFieldObjectClassType11(int count)
{
    FieldObjectClass *objectClass = CreateByteGrid(0x498, 0x78, count);
    s32 range;

    objectClass->param = 0;
    objectClass->shapeKind = 2;
    if (func_ov001_02063a38() == 4) {
        range = 0x867;
    } else {
        range = 0x59a;
    }
    objectClass->values[0] = range;
    objectClass->values[1] = 0;
    objectClass->values[2] = 0;
    objectClass->actorKind = 0;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = ActivateFieldSwitchObject;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseTaskWithCallback;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = ApplyRecordOrSetState;
    objectClass->hooks[10] = GetFieldOffset40_02082354;
    objectClass->hooks[9] = FieldObject_PlaceActor;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = NULL;
    objectClass->hooks[13] = NULL;
    objectClass->hooks[15] = FieldObject_DrawInstance;
    objectClass->classType = 0xb;
    objectClass->activeCount = 0;
    return objectClass;
}
