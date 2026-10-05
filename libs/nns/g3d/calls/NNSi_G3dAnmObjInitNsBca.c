#include "libs/nns/g3d/g3d_nsbca_internal.h"

void NNSi_G3dAnmObjInitNsBca(
    NNSG3dAnmObj *animationObject,
    void *resourceAnimation,
    const NNSG3dResMdl *model)
{
    u32 index;
    u16 *offsets;
    NNSG3dResJntAnm *jointAnimation;
    const NNSG3dResNodeInfo *nodeInfo;

    animationObject->resAnm = resourceAnimation;
    jointAnimation = (NNSG3dResJntAnm *)resourceAnimation;
    nodeInfo = NNS_G3dGetNodeInfo(model);
    animationObject->funcAnm = NNS_G3dFuncAnmJntNsBcaDefault;
    animationObject->numMapData = model->info.numNode;

    MI_CpuClear16(
        &animationObject->mapData[0],
        sizeof(u16) * animationObject->numMapData);

    offsets = (u16 *)((u8 *)jointAnimation + sizeof(NNSG3dResJntAnm));

    for (index = 0; index < jointAnimation->numNode; index++) {
        NNSG3dResJntAnmSRTTag *tag =
            (NNSG3dResJntAnmSRTTag *)((u8 *)jointAnimation + offsets[index]);

        animationObject->mapData[index] =
            (u16)((tag->tag >> NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT) |
                  NNS_G3D_ANMOBJ_MAPDATA_EXIST);
    }
}
