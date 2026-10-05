#include "nitro/types.h"

typedef struct MatAnmResult {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
} MatAnmResult;

typedef struct GeometryStateCache {
    u8 pad_00[8];
    u32 polygonAttr;
} GeometryStateCache;

extern GeometryStateCache NNS_G3dGlb_prmMatColor0;
extern void NNSi_G3dAnmCalcNsBma(MatAnmResult *result, const void *anmObj, u32 dataIdx);
extern s64 _s32_div_f(int numerator, int denominator);

void CalcMaterialAnimWithGlobalAlpha(MatAnmResult *result, const void *anmObj, u32 dataIdx)
{
    u16 globalAlpha = (NNS_G3dGlb_prmMatColor0.polygonAttr & 0x1f0000) >> 16;
    u32 attr;
    u16 alpha;

    NNSi_G3dAnmCalcNsBma(result, anmObj, dataIdx);
    attr = result->prmPolygonAttr;
    alpha = _s32_div_f(globalAlpha * (u16)((attr & 0x1f0000) >> 16), 0x1f);
    result->prmPolygonAttr = (attr & ~0x1f0000) | (alpha << 16);
}
