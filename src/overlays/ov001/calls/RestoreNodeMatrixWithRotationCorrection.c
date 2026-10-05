#include "nitro/types.h"
#include "nitro/fx_types.h"

extern BOOL NNS_G3dGetResultMtx(void *renderObj, VecFx32 *posMtx, void *nrmMtx, u32 nodeId);
extern fx32 VEC_Mag(VecFx32 *vec);
extern void func_01ffaff4(VecFx32 *dst, VecFx32 *src);
extern void QuaternionFromRotationMatrix(fx32 *quat, VecFx32 *mtx);
extern fx32 ScaleVector4ByReciprocalMagnitude(fx32 *dst, fx32 *src);
extern void MultiplyFixedPointQuaternions(fx32 *dst, fx32 *a, fx32 *b);
extern void QuaternionToRotationMatrix(VecFx32 *mtx, fx32 *quat);
extern void MTX_ScaleApply33(VecFx32 *dst, VecFx32 *src, fx32 x, fx32 y, fx32 z);

extern fx32 data_ov001_0209e460[4];

/* Restores a node matrix and optionally corrects its rotation. */
BOOL RestoreNodeMatrixWithRotationCorrection(u8 *node, VecFx32 *posMtx, u32 nodeId, BOOL applyCorrection)
{
    fx32 quat[4];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;

    if (NNS_G3dGetResultMtx(node + 0x20, posMtx, 0, nodeId)) {
        if (applyCorrection) {
            scaleX = VEC_Mag(&posMtx[0]);
            scaleY = VEC_Mag(&posMtx[1]);
            scaleZ = VEC_Mag(&posMtx[2]);
            func_01ffaff4(&posMtx[0], &posMtx[0]);
            func_01ffaff4(&posMtx[1], &posMtx[1]);
            func_01ffaff4(&posMtx[2], &posMtx[2]);
            QuaternionFromRotationMatrix(quat, posMtx);
            ScaleVector4ByReciprocalMagnitude(quat, quat);
            MultiplyFixedPointQuaternions(quat, quat, data_ov001_0209e460);
            QuaternionToRotationMatrix(posMtx, quat);
            MTX_ScaleApply33(posMtx, posMtx, scaleX, scaleY, scaleZ);
        }
        return TRUE;
    }
    return FALSE;
}
