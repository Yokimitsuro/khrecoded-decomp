#include "libs/nns/g3d/g3d_kernel_internal.h"

void releaseMdlTex_Internal_(
    NNSG3dResMat *mat,
    NNSG3dResDictTexToMatIdxData *binding)
{
    u8 *indices = (u8 *)mat + binding->offset;
    u32 i;

    for (i = 0; i < binding->numIdx; ++i) {
        NNSG3dResMatData *material =
            NNS_G3dGetMatDataByIdx(mat, indices[i]);

        material->texImageParam &=
            REG_G3_TEXIMAGE_PARAM_TGEN_MASK |
            REG_G3_TEXIMAGE_PARAM_FT_MASK |
            REG_G3_TEXIMAGE_PARAM_FS_MASK |
            REG_G3_TEXIMAGE_PARAM_RT_MASK |
            REG_G3_TEXIMAGE_PARAM_RS_MASK;
        material->magH = material->magW = FX32_ONE;
    }

    binding->flag &= ~1;
}
