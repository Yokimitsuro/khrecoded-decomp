#include "libs/nns/g3d/g3d_kernel_internal.h"

extern void MIi_CpuClear32(u32 data, void *destination, u32 size);
extern NNSG3dFuncAnmBlendMat NNS_G3dFuncBlendMatDefault;
extern NNSG3dFuncAnmBlendJnt NNS_G3dFuncBlendJntDefault;
extern NNSG3dFuncAnmBlendVis NNS_G3dFuncBlendVisDefault;

static inline void MI_CpuClear32(void *destination, u32 size)
{
    MIi_CpuClear32(0, destination, size);
}

void NNS_G3dRenderObjInit(
    NNSG3dRenderObj *pRenderObj,
    NNSG3dResMdl *pResMdl)
{
    MI_CpuClear32(pRenderObj, sizeof(NNSG3dRenderObj));

    pRenderObj->funcBlendMat = NNS_G3dFuncBlendMatDefault;
    pRenderObj->funcBlendJnt = NNS_G3dFuncBlendJntDefault;
    pRenderObj->funcBlendVis = NNS_G3dFuncBlendVisDefault;
    pRenderObj->resMdl = pResMdl;
}
