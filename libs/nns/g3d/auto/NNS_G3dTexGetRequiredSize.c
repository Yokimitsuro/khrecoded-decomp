#include "libs/nns/g3d/g3d_kernel_internal.h"

u32 NNS_G3dTexGetRequiredSize(const NNSG3dResTex *pTex)
{
    if (pTex) {
        return (u32)(pTex->texInfo.sizeTex << 3);
    }
    return 0;
}
