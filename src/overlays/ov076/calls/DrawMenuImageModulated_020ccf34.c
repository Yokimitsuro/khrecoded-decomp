#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct MenuImage {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

extern const MtxFx33 data_ov076_020cd23c;
extern MtxFx33 NNS_G3dGlb_prmBaseRot;
extern GeometryState NNS_G3dGlb_prmMatColor0;
extern void NNS_G3dGlbSetBaseScale(const VecFx32 *scale);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *trans);
extern void MI_Copy36B(const void *src, void *dst);
extern void NNS_G3dGlbFlushWVP(void);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    NNS_G3dGeBufferOP_N(op, &param, 1);
}

static inline void GeTexCoord(fx32 s, fx32 t)
{
    u32 data = (u16)(fx16)(s >> 8) | ((u16)(fx16)(t >> 8) << 16);
    NNS_G3dGeBufferOP_N(0x22, &data, 1);
}

static inline void GeVtx(fx16 x, fx16 y, fx16 z)
{
    u32 data[2];
    data[0] = (u16)x | ((u16)y << 16);
    data[1] = (u16)z;
    NNS_G3dGeBufferOP_N(0x23, data, 2);
}

void DrawMenuImageModulated_020ccf34(const MenuImage *images, u32 select, u32 pos, fx32 depth)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov076_020cd23c;
    const MenuImage *image = &images[select >> 16];

    scale.x = image->width << 12;
    scale.y = image->height << 12;
    scale.z = FX32_ONE;
    trans.x = (scale.x >> 1) + ((s16)(pos >> 16) << 12);
    trans.y = (192 << 12) - (((s16)pos << 12) + (scale.y >> 1));
    trans.z = depth;
    NNS_G3dGlbSetBaseScale(&scale);
    NNS_G3dGlbSetBaseTrans(&trans);
    MI_Copy36B(&rot, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbFlushWVP();
    NNS_G3dGeBufferOP_N(0x2b2a, image->texParams, 2);
    GeCommand1(0x29, 0x1f08c0);
    GeCommand1(0x20, (u16)select);
    GeCommand1(0x40, 1);
    GeTexCoord(0, 0);
    GeVtx(-0x800, 0x800, 0);
    GeTexCoord(scale.x, 0);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(scale.x, scale.y);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(0, scale.y);
    GeVtx(-0x800, -0x800, 0);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
