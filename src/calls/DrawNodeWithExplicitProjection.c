#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct G3dGlobalFlags {
    u8 pad_00[0xd4];
    u32 flags;
} G3dGlobalFlags;

extern G3dGlobalFlags NNS_G3dGlb;
extern MtxFx44 NNS_G3dGlb_projMtx;
extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 NNS_G3dGlb_camUp;
extern VecFx32 NNS_G3dGlb_camTarget;

extern void camera_commit_explicit_projection(void *camera, int top, int bottom, int left, int right);
extern void func_01ffb12c(void *node);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, MtxFx43 *mtx);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void DrawNodeWithExplicitProjection(void *node, void *camera, int top, int bottom, int left, int right)
{
    VecFx32 savedPosition = NNS_G3dGlb_camPos;
    VecFx32 savedUp = NNS_G3dGlb_camUp;
    VecFx32 savedTarget = NNS_G3dGlb_camTarget;
    MtxFx44 savedProjection = NNS_G3dGlb_projMtx;

    camera_commit_explicit_projection(camera, top, bottom, left, right);
    func_01ffb12c(node);
    NNS_G3dGlb_camPos = savedPosition;
    NNS_G3dGlb_camUp = savedUp;
    NNS_G3dGlb_camTarget = savedTarget;
    func_01ff9b70(&savedPosition, &savedUp, &savedTarget, &NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb.flags &= ~0xe8;
    MIi_CpuCopyFast(&savedProjection, &NNS_G3dGlb_projMtx, sizeof(MtxFx44));
    NNS_G3dGlb.flags &= ~0x50;
}
