#include "libs/nns/g3d/g3d_kernel_internal.h"

int NNS_G3dMdlGetMdlAlpha(const NNSG3dResMdl *model, u32 materialId)
{
    NNSG3dResMatData *material;

    material = NNS_G3dGetMatDataByIdx(NNS_G3dGetMat(model), materialId);
    return (material->polyAttr & 0x1f0000) >> 16;
}
