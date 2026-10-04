#include "libs/nns/g3d/g3d_kernel_internal.h"

extern BOOL removeLink_(NNSG3dAnmObj **list, NNSG3dAnmObj *item);

void NNS_G3dRenderObjRemoveAnmObj(
    NNSG3dRenderObj *pRenderObj,
    NNSG3dAnmObj *pAnmObj)
{
    if (removeLink_(&pRenderObj->anmMat, pAnmObj) ||
        removeLink_(&pRenderObj->anmJnt, pAnmObj) ||
        removeLink_(&pRenderObj->anmVis, pAnmObj)) {
        NNS_G3dRenderObjSetFlag(
            pRenderObj,
            NNS_G3D_RENDEROBJ_FLAG_HINT_OBSOLETE);
        return;
    }
}
