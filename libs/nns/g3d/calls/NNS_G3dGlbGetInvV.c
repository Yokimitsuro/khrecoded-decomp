#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern int MTX_Inverse43(const MtxFx43 *source, MtxFx43 *destination);

const MtxFx43 *NNS_G3dGlbGetInvV(void)
{
    if (!(NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_INVCAMERA_UPTODATE)) {
        MTX_Inverse43(&NNS_G3dGlb.cameraMtx, &NNS_G3dGlb.invCameraMtx);
        NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_INVCAMERA_UPTODATE;
    }
    return &NNS_G3dGlb.invCameraMtx;
}
