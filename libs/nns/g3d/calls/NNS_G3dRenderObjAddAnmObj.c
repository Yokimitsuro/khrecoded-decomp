#include "libs/nns/g3d/g3d_kernel_internal.h"

extern void addLink_(NNSG3dAnmObj **list, NNSG3dAnmObj *item);
extern void updateHintVec_(u32 *hint, const NNSG3dAnmObj *anmObj);

void NNS_G3dRenderObjAddAnmObj(
    NNSG3dRenderObj *pRenderObj,
    NNSG3dAnmObj *pAnmObj)
{
    const NNSG3dResAnmHeader *header;

    if (pAnmObj && pAnmObj->resAnm) {
        header = (const NNSG3dResAnmHeader *)pAnmObj->resAnm;

        switch (header->category0) {
        case 'M':
            updateHintVec_(pRenderObj->hintMatAnmExist, pAnmObj);
            addLink_(&pRenderObj->anmMat, pAnmObj);
            break;
        case 'J':
            updateHintVec_(pRenderObj->hintJntAnmExist, pAnmObj);
            addLink_(&pRenderObj->anmJnt, pAnmObj);
            break;
        case 'V':
            updateHintVec_(pRenderObj->hintVisAnmExist, pAnmObj);
            addLink_(&pRenderObj->anmVis, pAnmObj);
            break;
        default:
            break;
        }
    }
}
