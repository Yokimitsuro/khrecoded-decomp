#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelNode {
    u8 pad_00[0xb4];
    VecFx32 scale;
} ModelNode;

typedef struct ScaledModel {
    u8 pad_000[0x10];
    ModelNode node;
    u8 pad_0d0[0x2f0 - 0xd0];
    VecFx32 current;
    VecFx32 from;
    VecFx32 to;
    int elapsed;
    int duration;
    fx32 factor;
} ScaledModel;

extern int FX_Mul(int left, int right);
extern fx32 SafeFixedRatio(fx32 numerator, fx32 denominator);
extern fx32 FixedPointLerp(fx32 start, fx32 end, fx32 t);

void UpdateModelScaleTween(ScaledModel *model, int step)
{
    ModelNode *node = &model->node;
    VecFx32 scale;
    int duration = model->duration;

    if (duration != 0) {
        fx32 t;
        model->elapsed += step;
        if (model->elapsed >= duration) {
            model->elapsed = duration;
        }
        t = SafeFixedRatio(model->elapsed, model->duration);
        model->current.x = FixedPointLerp(model->from.x, model->to.x, t);
        model->current.y = FixedPointLerp(model->from.y, model->to.y, t);
        model->current.z = FixedPointLerp(model->from.z, model->to.z, t);
        if (model->elapsed >= model->duration) {
            model->duration = 0;
        }
    }
    scale.x = FX_Mul(model->current.x, model->factor);
    scale.y = FX_Mul(model->current.y, model->factor);
    scale.z = FX_Mul(model->current.z, model->factor);
    node->scale = scale;
}
