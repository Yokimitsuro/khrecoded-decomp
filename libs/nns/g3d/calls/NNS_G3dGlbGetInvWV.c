#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern void calcSrtCameraMtx_(void);

const MtxFx43 *NNS_G3dGlbGetInvWV(void)
{
    if (!(NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE)) {
        calcSrtCameraMtx_();
        NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE;
    }
    return &NNS_G3dGlb.invSrtCameraMtx;
}
