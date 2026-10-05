#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    VecFx32 row[3];
} MtxFx33;

typedef struct QuatFx32 {
    fx32 c[4];
} QuatFx32;

extern fx32 VEC_Mag(const VecFx32 *v);
extern int func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern void QuaternionFromRotationMatrix(QuatFx32 *dst, MtxFx33 *mtx);
extern void ScaleVector4ByReciprocalMagnitude(QuatFx32 *dst, QuatFx32 *src);
extern void MultiplyFixedPointQuaternions(QuatFx32 *dst, QuatFx32 *a, QuatFx32 *b);
extern void QuaternionToRotationMatrix(MtxFx33 *mtx, QuatFx32 *quat);
extern void func_01ff9158(MtxFx33 *dst, MtxFx33 *src, fx32 sx, fx32 sy, fx32 sz);
extern QuatFx32 data_02055838;

void ApplyQuaternionCorrectionToMatrix(MtxFx33 *mtx, s32 unused2, s32 unused3, s32 unused4) {
    fx32 scaleX, scaleY, scaleZ;
    QuatFx32 quat;

    scaleX = VEC_Mag(&mtx->row[0]);
    scaleY = VEC_Mag(&mtx->row[1]);
    scaleZ = VEC_Mag(&mtx->row[2]);
    func_01ffaff4(&mtx->row[0], &mtx->row[0]);
    func_01ffaff4(&mtx->row[1], &mtx->row[1]);
    func_01ffaff4(&mtx->row[2], &mtx->row[2]);
    QuaternionFromRotationMatrix(&quat, mtx);
    ScaleVector4ByReciprocalMagnitude(&quat, &quat);
    MultiplyFixedPointQuaternions(&quat, &quat, &data_02055838);
    QuaternionToRotationMatrix(mtx, &quat);
    func_01ff9158(mtx, mtx, scaleX, scaleY, scaleZ);
}
