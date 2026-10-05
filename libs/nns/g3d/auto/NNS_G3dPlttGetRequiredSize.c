#include "libs/nns/g3d/g3d_kernel_internal.h"

u32 NNS_G3dPlttGetRequiredSize(const NNSG3dResTex *pTex)
{
    if (pTex) {
        return (u32)(pTex->plttInfo.sizePltt << 3);
    }
    return 0;
}
