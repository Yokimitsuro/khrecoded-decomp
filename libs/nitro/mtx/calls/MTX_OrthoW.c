#include "libs/nitro/mtx/mtx_types_internal.h"

extern void FX_InvAsync(fx32 denominator);
extern fx64c FX_GetDivResultFx64c(void);

static inline void CP_SetDivImm64_32_NS_(u64 numerator, u32 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline void CP_SetDivImm64_32(u64 numerator, u32 denominator)
{
    CP_SetDivImm64_32_NS_(numerator, denominator);
}

static inline void FX_InvAsyncImm(fx32 denominator)
{
    CP_SetDivImm64_32((u64)0x1000 << 32, (u32)denominator);
}

static inline fx64c FX_GetInvResultFx64c(void)
{
    return FX_GetDivResultFx64c();
}

static inline fx32 FX_Mul32x64c(fx32 value, fx64c fraction)
{
    fx64c product = fraction * value + 0x80000000LL;
    return (fx32)(product >> 32);
}

void MTX_OrthoW(fx32 top, fx32 bottom, fx32 left, fx32 right,
                fx32 near, fx32 far, fx32 scaleW, MtxFx44 *mtx)
{
    fx64c inv1, inv2, inv3;

    {
        FX_InvAsync(right - left);
        mtx->elements._01 = 0;
        mtx->elements._02 = 0;
        mtx->elements._03 = 0;
        mtx->elements._10 = 0;
        mtx->elements._12 = 0;
        mtx->elements._13 = 0;
        mtx->elements._20 = 0;
        mtx->elements._21 = 0;
        mtx->elements._23 = 0;
        mtx->elements._33 = scaleW;
        inv1 = FX_GetInvResultFx64c();
    }
    {
        FX_InvAsyncImm(top - bottom);
        if (scaleW != 0x1000) {
            inv1 = (inv1 * scaleW) / 0x1000;
        }
        mtx->elements._00 = FX_Mul32x64c(0x1000 * 2, inv1);
        inv2 = FX_GetInvResultFx64c();
    }
    {
        FX_InvAsyncImm(near - far);
        if (scaleW != 0x1000) {
            inv2 = (inv2 * scaleW) / 0x1000;
        }
        mtx->elements._11 = FX_Mul32x64c(0x1000 * 2, inv2);
        inv3 = FX_GetInvResultFx64c();
    }

    if (scaleW != 0x1000) {
        inv3 = (inv3 * scaleW) / 0x1000;
    }
    mtx->elements._22 = FX_Mul32x64c(0x1000 * 2, inv3);
    mtx->elements._30 = FX_Mul32x64c(-right - left, inv1);
    mtx->elements._31 = FX_Mul32x64c(-top - bottom, inv2);
    mtx->elements._32 = FX_Mul32x64c(far + near, inv3);
}