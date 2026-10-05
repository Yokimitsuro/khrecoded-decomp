#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern const MtxFx43 *NNS_G3dGlbGetInvV(void);
extern const MtxFx44 *NNS_G3dGlbGetInvP(void);
extern void MTX_Copy43To44_(const MtxFx43 *source, MtxFx44 *destination);
extern void MTX_Concat44(
    const MtxFx44 *left,
    const MtxFx44 *right,
    MtxFx44 *result);

const MtxFx44 *NNS_G3dGlbGetInvVP(void)
{
    if (!(NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE)) {
        MtxFx44 camera;
        const MtxFx43 *inverseCamera = NNS_G3dGlbGetInvV();
        const MtxFx44 *inverseProjection = NNS_G3dGlbGetInvP();

        MTX_Copy43To44_(inverseCamera, &camera);
        MTX_Concat44(
            inverseProjection,
            &camera,
            &NNS_G3dGlb.invCameraProjMtx);
        NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE;
    }
    return &NNS_G3dGlb.invCameraProjMtx;
}
