#include "libs/nns/g3d/g3d_glbstate_internal.h"

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

void NNS_G3dGlbFlushP(void)
{
    u32 *commands = (u32 *)&NNS_G3dGlb;

    NNS_G3dGeBufferOP_N(commands[0], commands + 1, 0x34);
    NNS_G3dGlb.flag &= ~NNS_G3D_GLB_FLAG_FLUSH_WVP;
    NNS_G3dGlb.flag &= ~NNS_G3D_GLB_FLAG_FLUSH_VP;
}
