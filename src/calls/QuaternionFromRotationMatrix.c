#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Quaternion {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quaternion;

extern fx32 FX_Sqrt(fx32 value);
extern fx64c FX_DivFx64c(fx32 numerator, fx32 denominator);
extern u8 data_02055848[3];

void QuaternionFromRotationMatrix(Quaternion *quat, const MtxFx33 *mtx)
{
    fx32 trace;
    fx32 root;
    fx64c inverse;

    trace = mtx->m[0][0] + mtx->m[1][1] + mtx->m[2][2];

    if (trace > 0) {
        root = FX_Sqrt(trace + 0x1000);
        quat->w = root >> 1;

        inverse = FX_DivFx64c(0x800, root);
        quat->x = (fx32)((inverse * (mtx->m[1][2] - mtx->m[2][1]) + 0x80000000LL) >> 32);
        quat->y = (fx32)((inverse * (mtx->m[2][0] - mtx->m[0][2]) + 0x80000000LL) >> 32);
        quat->z = (fx32)((inverse * (mtx->m[0][1] - mtx->m[1][0]) + 0x80000000LL) >> 32);
    } else {
        int i, j, k;
        fx32 *axis[3];

        i = 0;
        if (mtx->m[1][1] > mtx->m[0][0]) {
            i = 1;
        }
        if (mtx->m[2][2] > mtx->m[i][i]) {
            i = 2;
        }
        j = data_02055848[i];
        k = data_02055848[j];

        root = FX_Sqrt(mtx->m[i][i] - mtx->m[j][j] - mtx->m[k][k] + 0x1000);

        axis[0] = &quat->x;
        axis[1] = &quat->y;
        axis[2] = &quat->z;
        *axis[i] = root >> 1;

        inverse = FX_DivFx64c(0x800, root);
        quat->w = (fx32)((inverse * (mtx->m[j][k] - mtx->m[k][j]) + 0x80000000LL) >> 32);
        *axis[j] = (fx32)((inverse * (mtx->m[i][j] + mtx->m[j][i]) + 0x80000000LL) >> 32);
        *axis[k] = (fx32)((inverse * (mtx->m[i][k] + mtx->m[k][i]) + 0x80000000LL) >> 32);
    }
}
