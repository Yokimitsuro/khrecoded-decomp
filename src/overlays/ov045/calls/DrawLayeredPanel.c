#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct PanelSprite {
    u32 texParams[2];
    u8 unknown_08[0x1a];
    u8 alpha : 5;
    u8 depthOffset : 3;
} PanelSprite;

extern const VecFx32 data_ov045_020c0770;
extern const VecFx32 data_ov045_020c0764;
extern const MtxFx33 data_ov045_020c07dc;
extern MtxFx33 NNS_G3dGlb_prmBaseRot;
extern GeometryState NNS_G3dGlb_prmMatColor0;
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *scale);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *trans);
extern void MI_Copy36B(const void *src, void *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);
extern void DrawTexturedQuad(fx32 left, fx32 top, fx32 right, fx32 bottom, fx16 x0, fx16 y0, fx16 x1, fx16 y1);

static inline void GeCommand1(u32 op, u32 param)
{
    NNS_G3dGeBufferOP_N(op, &param, 1);
}

void DrawLayeredPanel(PanelSprite *sprite, BOOL split)
{
    VecFx32 trans = data_ov045_020c0770;
    VecFx32 scale = data_ov045_020c0764;
    MtxFx33 rot = data_ov045_020c07dc;

    if (sprite->alpha != 0) {
        trans.z -= sprite->depthOffset;
        NNS_G3dGlbSetBaseScale(&scale);
        MI_Copy36B(&rot, &NNS_G3dGlb_prmBaseRot);
        NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
        NNS_G3dGlbSetBaseTrans(&trans);
        NNS_G3dGlbFlushWVP();
        NNS_G3dGeBufferOP_N(0x2b2a, sprite->texParams, 2);
        GeCommand1(0x29, (sprite->alpha << 16) | 0x8c0);
        GeCommand1(0x20, 0x7fff);
        if (split) {
            DrawTexturedQuad(0, 0, 0, 0, -0x800, -0x800, 0x800, -0x5ff);
            DrawTexturedQuad(0, 0, 0, 0x40000, -0x800, -0x5ff, -0x200, -0xab);
            DrawTexturedQuad(0, 0, 0x40000, 0x40000, -0x200, -0x5ff, 0x200, -0xab);
            DrawTexturedQuad(0x40000, 0, 0x40000, 0x40000, 0x200, -0x5ff, 0x800, -0xab);
            DrawTexturedQuad(0x40000, 0x40000, 0x40000, 0x40000, -0x800, -0xab, 0x800, 0x800);
            return;
        }
        DrawTexturedQuad(0, 0, 0, 0, -0x800, -0x800, 0x800, 0x800);
    }
}
