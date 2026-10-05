#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    NNS_G3dGeBufferOP_N(0x10, &mode, 1);
}

void NNS_G3dGlbFlushVP(void)
{
    NNS_G3dGeBufferOP_N(
        0x00001610,
        (u32 *)&NNS_G3dGlb.mtxmode_proj,
        (sizeof(NNS_G3dGlb.mtxmode_proj) + sizeof(NNS_G3dGlb.projMtx)) / 4);
    NNS_G3dGeBufferOP_N(
        0x19,
        (u32 *)&NNS_G3dGlb.cameraMtx,
        sizeof(NNS_G3dGlb.cameraMtx) / 4);
    NNS_G3dGeMtxMode(2);
    NNS_G3dGeBufferOP_N(0x15, (u32 *)&NNS_G3dGlb.cmd1, 0x16);

    NNS_G3dGlb.flag &= ~NNS_G3D_GLB_FLAG_FLUSH_WVP;
    NNS_G3dGlb.flag |= NNS_G3D_GLB_FLAG_FLUSH_VP;
}
