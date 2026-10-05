#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 _0[0x38];
    u32 flags;
    u8 _3c[0x1c];
    VecFx32 goalTarget;
    VecFx32 goalEye;
    u8 _70[0x18];
    VecFx32 liveTarget;
    VecFx32 liveEye;
} CameraState;

extern CameraState *data_ov043_020bd2e0;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 GetField28(void);
extern void TranslateCameraTarget_020bc92c(const VecFx32 *offset);
extern void TranslateCameraGoal_020bc9d4(const VecFx32 *offset);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

BOOL EaseCameraVectors(void) {
    CameraState *camera = data_ov043_020bd2e0;
    VecFx32 direction;
    VecFx32 offset;
    VecFx32 moved;
    VecFx32 *goals[2];
    VecFx32 *sources[2];
    u8 i;
    fx32 distance;
    fx32 step;
    goals[0] = &camera->goalEye;
    goals[1] = &camera->goalTarget;
    sources[0] = &camera->liveEye;
    sources[1] = &camera->liveTarget;
    for (i = 0; i < 2; i = (u8)(i + 1)) {
        VecFx32 *goal = goals[i];
        VecFx32 *source = sources[i];
        VEC_Subtract(source, goal, &direction);
        distance = func_01ffaff4(&direction, &direction);
        if (distance != 0) {
            step = (fx32)(((fx64)distance * 0x300 + 0x800) >> 12);
            if (step > distance) {
                step = distance;
            } else if (step < 0) {
                step = 0;
            }
            if (step < distance) {
                VEC_MultAdd(step, &direction, goals[i], &moved);
                *goals[i] = moved;
            } else {
                *goal = *source;
            }
        }
    }
    if (camera->flags & 8) {
        fx32 height = GetField28();
        offset = MakeVec(0, 0, -height);
        TranslateCameraTarget_020bc92c(&offset);
        TranslateCameraGoal_020bc9d4(&offset);
    }
    return TRUE;
}
