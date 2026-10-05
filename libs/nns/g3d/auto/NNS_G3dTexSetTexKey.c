#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNS_G3dTexSetTexKey(
    NNSG3dResTex *pTex,
    u32 texKey,
    u32 tex4x4Key)
{
    if (texKey > 0) {
        pTex->texInfo.vramKey = texKey;
    }

    if (tex4x4Key > 0) {
        pTex->tex4x4Info.vramKey = tex4x4Key;
    }
}
