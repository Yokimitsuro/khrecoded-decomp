#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x340];
    fx32 timeScale;
    u8 pad_344[0x7f0 - 0x344];
    u8 animModel[0x958 - 0x7f0];
    fx32 animStep;
} Actor;

extern const s16 data_02053580[];
extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void AdvanceModelAnimation(void *model, fx32 step, VecFx32 *out);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

void Actor_GetRootMotionDelta(Actor *actor, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 delta;
    int angle = GetLinkedAngleOffset_020cd104(actor) >> 4;
    fx32 scale;

    MTX_RotY33_(&rotation, -data_02053580[angle], -data_02053580[(0x400 - angle) & 0xfff]);
    AdvanceModelAnimation(actor->animModel, actor->animStep, &delta);
    scale = FX_Div(FX32_ONE, actor->timeScale);
    if (scale != FX32_ONE) {
        func_01ffafb4(scale, &delta, &delta);
    }
    MTX_MultVec33(&delta, &rotation, out);
}
