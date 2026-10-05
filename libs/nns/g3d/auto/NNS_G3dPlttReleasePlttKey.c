#include "libs/nns/g3d/g3d_kernel_internal.h"

u32 NNS_G3dPlttReleasePlttKey(NNSG3dResTex *pTex)
{
    u32 result;

    pTex->plttInfo.flag &= ~1;
    result = pTex->plttInfo.vramKey;
    pTex->plttInfo.vramKey = 0;
    return result;
}
