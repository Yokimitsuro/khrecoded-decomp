#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
} PanelPath;

typedef struct {
    u8 pad00[0x40];
    int prevState;
    int state;
    u8 pad48[4];
    PanelPath path;
    fx32 timer;
    fx32 duration;
    int easing;
    VecFx32 forward;
    VecFx32 up;
    VecFx32 savedPos;
    VecFx32 savedForward;
    VecFx32 savedUp;
    VecFx32 pathOut;
    VecFx32 pathOut2;
    VecFx32 savedTarget;
    VecFx32 stateTarget;
    u8 paddc[0x18];
    VecFx32 target;
} Panel;

extern Panel *data_ov044_020d0ec0;
extern PanelPath data_ov044_020d0e10[];

extern fx32 EaseProgress(fx32 time, fx32 duration, int easing);
extern void LerpVecFx32Q27InPlace(VecFx32 *current, const VecFx32 *target, s32 t);
extern s16 AngleBetweenVecs(const VecFx32 *a, const VecFx32 *b);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *axis, fx32 radians);
extern void EnterPanelState(int state);

#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))
#define IDX_TO_RAD(angle) ((fx32)((s64)(angle) * 0x6488 / 0x10000))

void StepPanelTransition(void)
{
    VecFx32 defaultTarget;
    fx32 progress;
    s32 lerpT;

    data_ov044_020d0ec0->timer += 0x1000;
    if (data_ov044_020d0ec0->timer < data_ov044_020d0ec0->duration) {
        progress = EaseProgress(data_ov044_020d0ec0->timer, data_ov044_020d0ec0->duration, data_ov044_020d0ec0->easing);
        lerpT = progress << 15;
        {
            const VecFx32 *goal = &data_ov044_020d0e10[data_ov044_020d0ec0->state].start;
            VecFx32 pos = data_ov044_020d0ec0->savedPos;
            LerpVecFx32Q27InPlace(&pos, goal, lerpT);
            data_ov044_020d0ec0->path.start = pos;
        }
        {
            fx32 angle = IDX_TO_RAD(AngleBetweenVecs(&data_ov044_020d0ec0->savedForward, &data_ov044_020d0ec0->pathOut));
            VecFx32 rotated = data_ov044_020d0ec0->savedForward;
            RotateVecTowardVec(&rotated, &data_ov044_020d0ec0->pathOut, FX_MUL(angle, progress));
            data_ov044_020d0ec0->forward = rotated;
        }
        {
            fx32 angle = IDX_TO_RAD(AngleBetweenVecs(&data_ov044_020d0ec0->savedUp, &data_ov044_020d0ec0->pathOut2));
            VecFx32 rotated = data_ov044_020d0ec0->savedUp;
            RotateVecTowardVec(&rotated, &data_ov044_020d0ec0->pathOut2, FX_MUL(angle, progress));
            data_ov044_020d0ec0->up = rotated;
        }
        if (data_ov044_020d0ec0->state == 6) {
            VecFx32 target = data_ov044_020d0ec0->savedTarget;
            LerpVecFx32Q27InPlace(&target, &data_ov044_020d0ec0->stateTarget, lerpT);
            data_ov044_020d0ec0->target = target;
        } else if (data_ov044_020d0ec0->prevState == 6) {
            VecFx32 fallback;
            VecFx32 target;
            fallback.x = 0;
            fallback.y = 0;
            fallback.z = -0x2333;
            defaultTarget = fallback;
            target = data_ov044_020d0ec0->savedTarget;
            LerpVecFx32Q27InPlace(&target, &defaultTarget, lerpT);
            data_ov044_020d0ec0->target = target;
        }
    } else {
        EnterPanelState(data_ov044_020d0ec0->state);
    }
}
