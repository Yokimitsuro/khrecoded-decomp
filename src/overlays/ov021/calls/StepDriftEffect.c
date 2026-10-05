#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x1c];
    VecFx32 shownPosition;
    u8 pad_28[8];
    fx32 speed;
    VecFx32 prevPosition;
    VecFx32 position;
    s32 progress;
    s32 angle;
} DriftEffect;

extern VecFx32 GetCameraOrbitOffset(s32 angle);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

static inline VecFx32 ScaledDirection(s32 angle, fx32 speed)
{
    VecFx32 step = GetCameraOrbitOffset(angle);
    ScaleVecFx32InPlace(&step, speed);
    return step;
}

void StepDriftEffect(DriftEffect *effect)
{
    effect->prevPosition = effect->position;
    effect->position = ScaledDirection(effect->angle, effect->speed);
    effect->progress = 0;
    effect->shownPosition = effect->prevPosition;
}
