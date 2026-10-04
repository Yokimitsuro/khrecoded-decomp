#include "libs/nns/g3d/g3d_kernel_internal.h"

extern u32 NNS_G3dAnmFmtNum;
extern NNSG3dAnmObjInitFunc NNS_G3dAnmObjInitFuncArray[];

void NNS_G3dAnmObjInit(
    NNSG3dAnmObj *pAnmObj,
    void *pResAnm,
    const NNSG3dResMdl *pResMdl,
    const NNSG3dResTex *pResTex)
{
    const NNSG3dResAnmHeader *hdr;
    u32 i;

    pAnmObj->frame = 0;
    pAnmObj->resAnm = pResAnm;
    pAnmObj->next = NULL;
    pAnmObj->priority = 127;
    pAnmObj->ratio = 0x1000;
    pAnmObj->resTex = pResTex;
    pAnmObj->numMapData = 0;
    pAnmObj->funcAnm = NULL;

    hdr = (const NNSG3dResAnmHeader *)pResAnm;
    for (i = 0; i < NNS_G3dAnmFmtNum; ++i) {
        if (NNS_G3dAnmObjInitFuncArray[i].category0 == hdr->category0 &&
            NNS_G3dAnmObjInitFuncArray[i].category1 == hdr->category1) {
            if (NNS_G3dAnmObjInitFuncArray[i].func) {
                (*NNS_G3dAnmObjInitFuncArray[i].func)(
                    pAnmObj,
                    pResAnm,
                    pResMdl);
            }
            break;
        }
    }
}
