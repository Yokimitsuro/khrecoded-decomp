#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct SpriteTexture {
    u8 unknown_00[0x04];
    u32 texParams[2];
} SpriteTexture;

extern const VecFx32 data_ov045_020c0788;
extern const VecFx32 data_ov045_020c077c;
extern const s16 data_02053580[];
extern MtxFx33 NNS_G3dGlb_prmBaseRot;
extern GeometryState NNS_G3dGlb_prmMatColor0;
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
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

void DrawRotatedSprite(SpriteTexture *sprite, int size, int angle)
{
    VecFx32 trans = data_ov045_020c0788;
    VecFx32 scale = data_ov045_020c077c;
    MtxFx33 rot;
    int angleIndex;

    if (size != 0) {
        scale.x = scale.y = size << 7;
        angleIndex = (u16)angle >> 4;
        MTX_RotZ33_(&rot, data_02053580[angleIndex], data_02053580[(0x400 - angleIndex) & 0xfff]);
        NNS_G3dGlbSetBaseScale(&scale);
        MI_Copy36B(&rot, &NNS_G3dGlb_prmBaseRot);
        NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
        NNS_G3dGlbSetBaseTrans(&trans);
        NNS_G3dGlbFlushWVP();
        NNS_G3dGeBufferOP_N(0x2b2a, sprite->texParams, 2);
        GeCommand1(0x29, 0x1f08c0);
        GeCommand1(0x20, 0x7fff);
        DrawTexturedQuad(0, 0, 0x80000, 0x80000, -0x800, -0x800, 0x800, 0x800);
    }
}
