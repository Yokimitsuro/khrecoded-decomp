#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern void MTX_Concat43(
    const MtxFx43 *left,
    const MtxFx43 *right,
    MtxFx43 *result);
extern void MTX_ScaleApply43(
    const MtxFx43 *source,
    MtxFx43 *destination,
    fx32 x,
    fx32 y,
    fx32 z);
extern int MTX_Inverse43(const MtxFx43 *source, MtxFx43 *destination);

void calcSrtCameraMtx_(void)
{
    MTX_Concat43(
        (MtxFx43 *)&NNS_G3dGlb.prmBaseRot,
        &NNS_G3dGlb.cameraMtx,
        &NNS_G3dGlb.srtCameraMtx);
    MTX_ScaleApply43(
        &NNS_G3dGlb.srtCameraMtx,
        &NNS_G3dGlb.srtCameraMtx,
        NNS_G3dGlb.prmBaseScale.x,
        NNS_G3dGlb.prmBaseScale.y,
        NNS_G3dGlb.prmBaseScale.z);
    MTX_Inverse43(&NNS_G3dGlb.srtCameraMtx, &NNS_G3dGlb.invSrtCameraMtx);
}
