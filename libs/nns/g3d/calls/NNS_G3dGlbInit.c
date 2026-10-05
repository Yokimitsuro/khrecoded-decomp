#include "libs/nns/g3d/g3d_glbstate_internal.h"

#define FX32_ONE 0x1000

extern void MTX_Identity33_(MtxFx33 *matrix);
extern void MTX_Identity43_(MtxFx43 *matrix);
extern void MTX_Identity44_(MtxFx44 *matrix);

void NNS_G3dGlbInit(void)
{
    NNS_G3dGlb.cmd0 = 0x17101610;
    NNS_G3dGlb.mtxmode_proj = 0;
    NNS_G3dGlb.mtxmode_posvec = 2;
    NNS_G3dGlb.cmd1 = 0x60293130;
    NNS_G3dGlb.cmd2 = 0x002a1b19;

    MTX_Identity43_(&NNS_G3dGlb.cameraMtx);
    MTX_Identity44_(&NNS_G3dGlb.projMtx);

    NNS_G3dGlb.prmMatColor0 = 0x4210c210;
    NNS_G3dGlb.prmMatColor1 = 0x4210c210;
    NNS_G3dGlb.prmPolygonAttr = 0x001f008f;
    NNS_G3dGlb.prmViewPort = 0xbfff0000;

    NNS_G3dGlb.prmBaseTrans.x = 0;
    NNS_G3dGlb.prmBaseTrans.y = 0;
    NNS_G3dGlb.prmBaseTrans.z = 0;
    MTX_Identity33_(&NNS_G3dGlb.prmBaseRot);
    NNS_G3dGlb.prmBaseScale.x = FX32_ONE;
    NNS_G3dGlb.prmBaseScale.y = FX32_ONE;
    NNS_G3dGlb.prmBaseScale.z = FX32_ONE;
    NNS_G3dGlb.prmTexImageParam = 0;
    NNS_G3dGlb.flag = 0;

    NNS_G3dGlb.camPos.z = 0;
    NNS_G3dGlb.camPos.y = 0;
    NNS_G3dGlb.camPos.x = 0;
    NNS_G3dGlb.camUp.z = 0;
    NNS_G3dGlb.camUp.x = 0;
    NNS_G3dGlb.camUp.y = FX32_ONE;
    NNS_G3dGlb.camTarget.y = 0;
    NNS_G3dGlb.camTarget.x = 0;
    NNS_G3dGlb.camTarget.z = -FX32_ONE;
}
