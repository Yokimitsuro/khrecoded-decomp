#include "libs/nns/g3d/g3d_kernel_internal.h"

extern void bindMdlPltt_Internal_(
    NNSG3dResMat *mat,
    NNSG3dResDictPlttToMatIdxData *binding,
    const NNSG3dResTex *tex,
    const NNSG3dResDictPlttData *paletteData);

BOOL NNS_G3dBindMdlPltt(
    NNSG3dResMdl *model,
    const NNSG3dResTex *tex)
{
    NNSG3dResMat *mat;
    NNSG3dResDict *dict;
    u32 i;
    BOOL result = TRUE;

    mat = NNS_G3dGetMat(model);
    dict = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictPlttToMatList);

    for (i = 0; i < dict->numEntry; ++i) {
        const NNSG3dResName *name = NNS_G3dGetResNameByIdx(dict, i);
        const NNSG3dResDictPlttData *paletteData =
            NNS_G3dGetPlttDataByName(tex, name);

        if (paletteData) {
            NNSG3dResDictPlttToMatIdxData *binding =
                NNS_G3dGetResDataByIdx(dict, i);

            if (!(binding->flag & 1)) {
                bindMdlPltt_Internal_(mat, binding, tex, paletteData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}
