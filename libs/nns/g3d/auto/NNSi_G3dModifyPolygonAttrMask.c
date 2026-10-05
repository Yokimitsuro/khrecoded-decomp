#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNSi_G3dModifyPolygonAttrMask(NNSG3dResMdl *model, BOOL enabled, u32 mask)
{
    u32 materialCount;
    u32 materialId;
    NNSG3dResMat *materials;

    materialCount = model->info.numMat;
    materials = NNS_G3dGetMat(model);

    for (materialId = 0; materialId < materialCount; ++materialId) {
        NNSG3dResMatData *material =
            NNS_G3dGetMatDataByIdx(materials, materialId);

        if (enabled) {
            material->polyAttrMask |= mask;
        } else {
            material->polyAttrMask &= ~mask;
        }
    }
}
