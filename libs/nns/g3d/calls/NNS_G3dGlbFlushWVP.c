#include "libs/nns/g3d/g3d_glbstate_internal.h"

#define NULL ((void *)0)

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    NNS_G3dGeBufferOP_N(0x10, &mode, 1);
}

void NNS_G3dGlbFlushWVP(void)
{
    NNS_G3dGeBufferOP_N(
        0x00001610,
        (u32 *)&NNS_G3dGlb.mtxmode_proj,
        (sizeof(NNS_G3dGlb.mtxmode_proj) + sizeof(NNS_G3dGlb.projMtx)) / 4);

    NNS_G3dGeBufferOP_N(
        0x19,
        (u32 *)&NNS_G3dGlb.cameraMtx,
        sizeof(NNS_G3dGlb.cameraMtx) / 4);

    NNS_G3dGeBufferOP_N(
        0x00001b19,
        (u32 *)&NNS_G3dGlb.prmBaseRot,
        (sizeof(NNS_G3dGlb.prmBaseRot) +
         sizeof(NNS_G3dGlb.prmBaseTrans) +
         sizeof(NNS_G3dGlb.prmBaseScale)) / 4);

    NNS_G3dGeMtxMode(2);

    NNS_G3dGeBufferOP_N(NNS_G3dGlb.cmd1, (u32 *)&NNS_G3dGlb.cmd1 + 1, 4);
    NNS_G3dGeBufferOP_N(0x15, NULL, 0);
    NNS_G3dGeBufferOP_N(0x2a, &NNS_G3dGlb.prmTexImageParam, 1);

    NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_FLUSH_WVP;
    NNS_G3dGlb.flag &= ~NNS_G3D_GLB_FLAG_FLUSH_VP;
}
