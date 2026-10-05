#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelInstance {
    u8 pad_00[0x7e];
    u16 pitch;
} ModelInstance;

typedef struct ActorModel {
    u32 flags;
    ModelInstance instance;
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
} Actor;

extern const s16 data_02053580[];

extern int GetLinkedAngleOffset_020cd104(Actor *actor);
extern void GetAttachmentOffset_020c8928(VecFx32 *out, Actor *actor, int jointIndex);
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void Actor_GetRotatedJointPosition(VecFx32 *out, Actor *actor)
{
    VecFx32 result;
    VecFx32 offset;
    VecFx32 baseJoint;
    MtxFx33 yawRotation;
    MtxFx33 pitchRotation;
    ModelInstance *instance = &actor->model->instance;
    int heading = GetLinkedAngleOffset_020cd104(actor);
    int angleIndex;

    GetAttachmentOffset_020c8928(&baseJoint, actor, 2);
    GetAttachmentOffset_020c8928(&offset, actor, 3);
    angleIndex = instance->pitch >> 4;
    MTX_RotZ33_(&pitchRotation, data_02053580[angleIndex], data_02053580[(0x400 - angleIndex) & 0xfff]);
    angleIndex = heading >> 4;
    MTX_RotY33_(&yawRotation, -data_02053580[angleIndex], -data_02053580[(0x400 - angleIndex) & 0xfff]);
    MTX_MultVec33(&offset, &pitchRotation, &offset);
    MTX_MultVec33(&offset, &yawRotation, &offset);
    VEC_Add(&offset, Actor_GetModelPosition(actor), &result);
    *out = result;
}
