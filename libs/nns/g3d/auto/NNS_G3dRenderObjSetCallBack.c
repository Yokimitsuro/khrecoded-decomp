#include "libs/nns/g3d/g3d_kernel_internal.h"

void NNS_G3dRenderObjSetCallBack(
    NNSG3dRenderObj *pRenderObj,
    NNSG3dSbcCallBackFunc func,
    u8 *unused,
    u8 command,
    int timing)
{
    pRenderObj->cbFunc = func;
    pRenderObj->cbCmd = command;
    pRenderObj->cbTiming = (u8)timing;
}
