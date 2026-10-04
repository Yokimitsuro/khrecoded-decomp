#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNS_G3dRenderObjResetCallBack(NNSG3dRenderObj *pRenderObj)
{
    pRenderObj->cbFunc = NULL;
    pRenderObj->cbCmd = 0;
    pRenderObj->cbTiming = 0;
}
