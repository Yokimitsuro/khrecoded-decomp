#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);
extern int Math_AcosIdx(fx32 cosine);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *target, fx32 angle);

static inline void SnapToDirection(VecFx32 *vec, const VecFx32 *dir)
{
    fx32 length = VEC_Mag(vec);
    VecFx32 result = *dir;
    func_01ffaff4(&result, &result);
    ScaleVecFx32InPlace(&result, length);
    *vec = result;
}

void TurnVecTowardVecLimited(VecFx32 *vec, const VecFx32 *target, fx32 maxAngle)
{
    VecFx32 vecDir;
    VecFx32 targetDir;
    VecFx32 vecNorm;
    VecFx32 targetNorm;
    fx32 cosine;
    fx32 angle;

    VEC_Normalize(target, &targetNorm);
    targetDir = targetNorm;
    VEC_Normalize(vec, &vecNorm);
    vecDir = vecNorm;
    cosine = VEC_DotProduct(&vecDir, &targetDir);
    if (cosine > 0xfae) {
        SnapToDirection(vec, target);
        return;
    }
    if (cosine > 0x1000) {
        cosine = 0x1000;
    } else if (cosine < -0x1000) {
        cosine = -0x1000;
    }
    angle = ((s64)(s16)Math_AcosIdx(cosine) * 0x6488) / 0x10000;
    if (maxAngle >= angle - 0x20) {
        SnapToDirection(vec, target);
        return;
    }
    RotateVecTowardVec(vec, target, maxAngle);
}
