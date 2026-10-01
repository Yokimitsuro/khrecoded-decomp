#include "libs/nitro/mtx/mtx_types_internal.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx64c FX_GetDivResultFx64c(void);
extern fx64c _ll_sdiv(fx64c numerator, fx64c denom);
extern fx32 FX_GetDivResult(void);

static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline fx32 RoundFx64cToFx32(u64 v)
{
    return (fx32)((v + 0x80000000ULL) >> 32);
}

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((fx64c)a * b + 0x800) >> 12);
}

void Camera_BuildProjectionMtx(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 near, fx32 far,
                   fx32 scaleW, MtxFx44 *mtx)
{
    fx64c recipDepth;
    fx32 fovCot;

    fovCot = FX_Div(fovyCos, fovySin);
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(near - far));
    if (scaleW != 0x1000)
        fovCot = (fovCot * scaleW) / 0x1000;

    mtx->elements._01 = 0;
    mtx->elements._02 = 0;
    mtx->elements._03 = 0;
    mtx->elements._10 = 0;
    mtx->elements._11 = fovCot;
    mtx->elements._12 = 0;
    mtx->elements._13 = 0;
    mtx->elements._20 = 0;
    mtx->elements._21 = 0;
    mtx->elements._23 = -scaleW;
    mtx->elements._30 = 0;
    mtx->elements._31 = 0;
    mtx->elements._33 = 0;

    recipDepth = FX_GetDivResultFx64c();
    CP_SetDivImm64_64_NS_((u64)fovCot << 32, (u64)(u32)aspect);
    if (scaleW != 0x1000)
        recipDepth = _ll_sdiv(recipDepth * scaleW, 0x1000);

    mtx->elements._22 = RoundFx64cToFx32((u64)(recipDepth * (far + near)));
    mtx->elements._32 = RoundFx64cToFx32((u64)(recipDepth * FX_Mul(near * 2, far)));
    mtx->elements._00 = FX_GetDivResult();
}
