#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x18e60];
    VecFx32 points[1];
} PathData;

extern const s16 data_02053580[];
extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern PathData *func_ov001_0209c3e8(void);
extern s64 _ll_mul(s64 a, s64 b);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void MTX_RotX33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

int ScriptCmd_RotatePathPoint(void *context, TaggedValue *operands) {
    TaggedValue *index = ResolveTaggedValueRef(context, &operands[0]);
    TaggedValue *pitchArg = ResolveTaggedValueRef(context, &operands[1]);
    TaggedValue *yawArg = ResolveTaggedValueRef(context, &operands[2]);
    PathData *path;
    VecFx32 *point;
    MtxFx33 pitchMtx;
    MtxFx33 yawMtx;
    MtxFx33 rotation;
    u16 yaw;
    u16 pitch;
    ResolveTaggedValueRef(context, &operands[3]);
    path = func_ov001_0209c3e8();
    point = &path->points[index->value];
    MTX_Identity33_(&pitchMtx);
    MTX_Identity33_(&yawMtx);
    pitch = (u16)((_ll_mul(TaggedValueToFixed(pitchArg), 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    yaw = (u16)((_ll_mul(TaggedValueToFixed(yawArg), 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    MTX_RotX33_(&pitchMtx, data_02053580[pitch >> 4], data_02053580[(0x400 - (pitch >> 4)) & 0xfff]);
    MTX_RotY33_(&yawMtx, data_02053580[yaw >> 4], data_02053580[(0x400 - (yaw >> 4)) & 0xfff]);
    MTX_Concat33(&pitchMtx, &yawMtx, &rotation);
    MTX_MultVec33(point, &rotation, point);
    return 0;
}
