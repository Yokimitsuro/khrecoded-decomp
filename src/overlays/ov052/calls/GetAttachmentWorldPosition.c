#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad0[0x7e];
    u16 roll;
} BodyPose;

typedef struct {
    u32 flags;
    BodyPose pose;
} BodyModel;

extern s16 data_02053580[];
extern u16 GetLinkedAngleOffset(int entity);
extern VecFx32 *func_ov052_020ceb74(int entity);
extern void GetAttachmentOffset(VecFx32 *out, int owner, int slot);
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void GetAttachmentWorldPosition(VecFx32 *out, int entity, int slot)
{
    VecFx32 result;
    VecFx32 offset;
    VecFx32 base;
    MtxFx33 facing;
    MtxFx33 roll;
    BodyPose *pose = &(*(BodyModel **)(entity + 0x230))->pose;
    int angle = GetLinkedAngleOffset(entity);
    int index;
    GetAttachmentOffset(&base, entity, 2);
    GetAttachmentOffset(&offset, entity, slot);
    index = pose->roll >> 4;
    MTX_RotZ33_(&roll, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    index = angle >> 4;
    MTX_RotY33_(&facing, -data_02053580[index], -data_02053580[(0x400 - index) & 0xfff]);
    MTX_MultVec33(&offset, &roll, &offset);
    MTX_MultVec33(&offset, &facing, &offset);
    VEC_Add(&offset, func_ov052_020ceb74(entity), &result);
    *out = result;
}
