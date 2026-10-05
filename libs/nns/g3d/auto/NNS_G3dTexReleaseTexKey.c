#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNS_G3dTexReleaseTexKey(
    NNSG3dResTex *pTex,
    u32 *texKey,
    u32 *tex4x4Key)
{
    if (texKey) {
        pTex->texInfo.flag &= ~1;
        *texKey = pTex->texInfo.vramKey;
        pTex->texInfo.vramKey = 0;
    }

    if (tex4x4Key) {
        pTex->tex4x4Info.flag &= ~1;
        *tex4x4Key = pTex->tex4x4Info.vramKey;
        pTex->tex4x4Info.vramKey = 0;
    }
}
