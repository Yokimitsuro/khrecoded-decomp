#include "libs/nns/g3d/g3d_glbstate_internal.h"

#define FX32_SHIFT 12

extern void MI_Copy64B(const void *source, void *destination);
extern void MTX_Identity44_(MtxFx44 *matrix);
extern fx64c FX_InvFx64c(fx32 value);

static inline fx32 FX_Mul32x64c(fx32 value, fx64c factor)
{
    fx64c product = factor * value + 0x80000000LL;
    return (fx32)(product >> 32);
}

int mtx_inverse44(const MtxFx44 *source, MtxFx44 *destination)
{
    MtxFx44 work;
    int i;
    int j;
    int k;
    fx64c reciprocal;
    fx32 factor;

    MI_Copy64B(source, &work);
    MTX_Identity44_(destination);

    for (i = 0; i < 4; ++i) {
        fx32 max = 0;
        int pivot = i;

        for (k = i; k < 4; ++k) {
            fx32 value = work.m[k][i] < 0 ? -work.m[k][i] : work.m[k][i];

            if (value > max) {
                max = value;
                pivot = k;
            }
        }

        if (max == 0) {
            return -1;
        }

        if (pivot != i) {
            for (k = 0; k < 4; ++k) {
                fx32 value = work.m[i][k];
                work.m[i][k] = work.m[pivot][k];
                work.m[pivot][k] = value;

                value = destination->m[i][k];
                destination->m[i][k] = destination->m[pivot][k];
                destination->m[pivot][k] = value;
            }
        }

        reciprocal = FX_InvFx64c(work.m[i][i]);
        for (j = 0; j < 4; ++j) {
            work.m[i][j] = FX_Mul32x64c(work.m[i][j], reciprocal);
            destination->m[i][j] =
                FX_Mul32x64c(destination->m[i][j], reciprocal);
        }

        for (k = 0; k < 4; ++k) {
            if (k == i) {
                continue;
            }

            factor = work.m[k][i];
            for (j = 0; j < 4; ++j) {
                work.m[k][j] -=
                    (fx32)(((fx64)factor * work.m[i][j]) >> FX32_SHIFT);
                destination->m[k][j] -=
                    (fx32)(((fx64)factor * destination->m[i][j]) >> FX32_SHIFT);
            }
        }
    }

    return 0;
}
