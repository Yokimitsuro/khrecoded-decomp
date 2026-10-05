#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern int mtx_inverse44(const MtxFx44 *source, MtxFx44 *destination);

const MtxFx44 *NNS_G3dGlbGetInvP(void)
{
    if (!(NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE)) {
        mtx_inverse44(&NNS_G3dGlb.projMtx, &NNS_G3dGlb.invProjMtx);
        NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE;
    }
    return &NNS_G3dGlb.invProjMtx;
}
