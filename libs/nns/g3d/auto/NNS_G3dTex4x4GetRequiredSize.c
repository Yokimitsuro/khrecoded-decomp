#include "libs/nns/g3d/g3d_kernel_internal.h"

u32 NNS_G3dTex4x4GetRequiredSize(const NNSG3dResTex *pTex)
{
    if (pTex) {
        return (u32)(pTex->tex4x4Info.sizeTex << 3);
    }
    return 0;
}
