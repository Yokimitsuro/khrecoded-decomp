#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct AnimatedModel {
    u8 pad0[0x20];
    u32 drawFlags;
    u8 pad24[0xfc];
    fx32 frame;
    int state;
    u8 joints[4];
} AnimatedModel;

extern fx32 func_0202f4cc(AnimatedModel *model, int channel);
extern int *func_01ffb2f8(AnimatedModel *model, int channel, fx32 frame);
extern void func_01ffb12c(AnimatedModel *model);
extern void GetCurrentNodeOffset(AnimatedModel *model, void *joints, VecFx32 *out);

void AdvanceModelAnimation(AnimatedModel *model, fx32 step, VecFx32 *out)
{
    fx32 frame;
    fx32 last;

    if (model->state != 2) {
        out->z = 0;
        out->y = 0;
        out->x = 0;
        return;
    }
    frame = model->frame + step;
    last = func_0202f4cc(model, 0) - FX32_ONE;
    if (frame > last) {
        frame = last;
    }
    func_01ffb2f8(model, 0, frame);
    model->drawFlags |= 3;
    func_01ffb12c(model);
    model->drawFlags &= ~3;
    GetCurrentNodeOffset(model, model->joints, out);
    model->frame = frame;
}
