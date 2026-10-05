#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

BOOL ComputePushTowardTarget(const VecFx32 *target, const VecFx32 *center, fx32 *speed, VecFx32 *push)
{
    VecFx32 eye = *target;
    VecFx32 diff;
    VecFx32 dir;
    BOOL close = FALSE;
    fx32 dist;
    fx32 step;
    fx32 height;

    height = eye.y + 0x5000;
    eye.y = height;
    if (height > 0xc000) {
        height = 0xc000;
    }
    eye.y = height;
    func_01ff9e3c(&eye, center, &diff);
    dist = VEC_Mag(&diff);
    if (dist == 0) {
        diff.x = 1;
    }
    step = *speed + 0x66;
    *speed = step;
    if (step > 0xccd) {
        step = 0xccd;
    }
    *speed = step;
    if (dist < 0x1b33) {
        *speed = step * 7 / 10;
        close = TRUE;
    }
    if (dist < step) {
        step = dist;
    }
    dir = diff;
    func_01ffaff4(&dir, &dir);
    ScaleVecFx32InPlace(&dir, step);
    *push = dir;
    return close;
}
