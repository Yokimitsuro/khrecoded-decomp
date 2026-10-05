#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNS_G3dReleaseMdlPltt(NNSG3dResMdl *model)
{
    NNSG3dResMat *mat;
    NNSG3dResDict *dict;
    u32 i;

    mat = NNS_G3dGetMat(model);
    dict = (NNSG3dResDict *)((u8 *)mat + mat->ofsDictPlttToMatList);

    for (i = 0; i < dict->numEntry; ++i) {
        NNSG3dResDictPlttToMatIdxData *binding =
            NNS_G3dGetResDataByIdx(dict, i);

        if (binding->flag & 1) {
            binding->flag &= ~1;
        }
    }
}
