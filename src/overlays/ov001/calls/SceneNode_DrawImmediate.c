#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x1e];
    u8 renderObj[0x5c];
    u16 angleY;
    u16 angleX;
    MtxFx43 matrix;
    VecFx32 position;
    u8 pad_bc[0x40];
    u16 colorScale;
} SceneNode;

typedef struct GeometryStateCache {
    u8 pad_00[0x54];
    u32 flags;
} GeometryStateCache;

extern VecFx32 NNS_G3dGlb_prmBaseScale;
extern MtxFx43 NNS_G3dGlb_prmBaseRot;
extern GeometryStateCache NNS_G3dGlb_prmMatColor0;
extern void UpdateNodeRotationYZ(SceneNode *node);
extern void NNS_G3dGlbFlushVP(void);
extern void func_01fff67c(int packedRgb);
extern void func_01ffe1bc(void *renderObj);

void SceneNode_DrawImmediate(SceneNode *node) {
    NNS_G3dGlb_prmBaseScale = node->position;
    UpdateNodeRotationYZ(node);
    NNS_G3dGlb_prmBaseRot = node->matrix;
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbFlushVP();
    if (node->flags & 0x40) {
        func_01fff67c(node->colorScale);
    }
    func_01ffe1bc(node->renderObj);
}
