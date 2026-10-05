#include "libs/nns/g3d/g3d_kernel_internal.h"

extern void bindMdlTex_Internal_(
    NNSG3dResMat *mat,
    NNSG3dResDictTexToMatIdxData *binding,
    const NNSG3dResTex *tex,
    const NNSG3dResDictTexData *texData);

BOOL NNS_G3dBindMdlTex(
    NNSG3dResMdl *model,
    const NNSG3dResTex *tex)
{
    NNSG3dResMat *mat;
    NNSG3dResDict *dict;
    u32 i;
    BOOL result = TRUE;

    mat = NNS_G3dGetMat(model);
    dict = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictTexToMatList);

    for (i = 0; i < dict->numEntry; ++i) {
        const NNSG3dResName *name = NNS_G3dGetResNameByIdx(dict, i);
        const NNSG3dResDictTexData *texData =
            NNS_G3dGetTexDataByName(tex, name);

        if (texData) {
            NNSG3dResDictTexToMatIdxData *binding =
                NNS_G3dGetResDataByIdx(dict, i);

            if (!(binding->flag & 1)) {
                bindMdlTex_Internal_(mat, binding, tex, texData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}
