#include "libs/nns/g3d/g3d_glbstate_internal.h"

void NNS_G3dGlbSetBaseTrans(const VecFx32 *translation)
{
    if (translation == 0) {
        return;
    }

    NNS_G3dGlb.prmBaseTrans = *translation;
    NNS_G3dGlb.flag &=
        ~(NNS_G3D_GLB_FLAG_INVBASE_UPTODATE |
          NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE |
          NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
}
