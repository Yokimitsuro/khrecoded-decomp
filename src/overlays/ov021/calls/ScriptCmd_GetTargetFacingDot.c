#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2e6];
    u16 facing;
} StageTarget;

typedef struct {
    void *actor;
    u32 pad_04;
    StageTarget *target;
} StageGlobals;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultTag;
    u16 pad_2e;
    s32 result;
} ScriptContext;

extern StageGlobals data_ov021_020b56c4;
extern s16 data_02053580[];
extern void NotifySceneObjectHandler(StageTarget *target, VecFx32 *out);
extern VecFx32 *func_ov001_02090f2c(StageTarget *target);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

int ScriptCmd_GetTargetFacingDot(ScriptContext *context)
{
    StageTarget *target = data_ov021_020b56c4.target;
    VecFx32 lookPos;
    VecFx32 basePos;
    VecFx32 delta;
    VecFx32 facing;
    fx32 dot;

    if (target == NULL) {
        return 0;
    }
    NotifySceneObjectHandler(target, &lookPos);
    basePos = *func_ov001_02090f2c(target);
    VEC_Subtract(&lookPos, &basePos, &delta);
    delta.y = 0;
    VEC_Normalize(&delta, &delta);
    facing.x = data_02053580[target->facing >> 4];
    facing.y = 0;
    facing.z = data_02053580[(0x400 - (target->facing >> 4)) & 0xfff];
    VEC_Normalize(&facing, &facing);
    dot = VEC_DotProduct(&delta, &facing);
    context->resultTag = 0x10;
    context->result = dot;
    return 0;
}
