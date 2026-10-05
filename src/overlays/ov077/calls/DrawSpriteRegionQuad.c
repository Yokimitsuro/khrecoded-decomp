#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

typedef struct SpriteTexture {
    u32 unknown_00;
    u32 texParams[2];
} SpriteTexture;

typedef struct SpriteRegion {
    SpriteTexture *texture;
    s16 x;
    s16 y;
    fx32 depth;
    u16 u;
    u16 v;
    u16 width;
    u16 height;
    u16 palette;
} SpriteRegion;

extern const MtxFx33 data_ov077_020ca194;
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

void DrawSpriteRegionQuad(const SpriteRegion *region, BOOL highlighted)
{
    VecFx32 trans;
    VecFx32 scale;
    MtxFx33 rot = data_ov077_020ca194;
    fx32 u;
    fx32 v;
    u32 polygonId;

    scale.x = region->width << 12;
    scale.y = region->height << 12;
    scale.z = FX32_ONE;
    trans.x = (region->x << 12) + (region->width << 11);
    trans.y = (192 << 12) - ((region->y << 12) + (region->height << 11));
    trans.z = region->depth;
    if (region->y <= 0) {
        scale.y += FX32_ONE;
    }
    NNS_G3dGlbSetBaseScale(&scale);
    NNS_G3dGlbSetBaseTrans(&trans);
    MI_Copy36B(&rot, &NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb_prmMatColor0.flags &= ~0xa4;
    NNS_G3dGlbFlushWVP();
    u = region->u << 12;
    v = region->v << 12;
    scale.x += u;
    scale.y += v;
    NNS_G3dGeBufferOP_N(0x2b2a, region->texture->texParams, 2);
    polygonId = 2;
    if (!highlighted) {
        polygonId = 0;
    }
    GeCommand1(0x29, 0x1f08c0 | (polygonId << 4));
    GeCommand1(0x20, region->palette);
    GeCommand1(0x40, 1);
    GeTexCoord(u, v);
    GeVtx(-0x800, 0x800, 0);
    GeTexCoord(scale.x, v);
    GeVtx(0x800, 0x800, 0);
    GeTexCoord(scale.x, scale.y);
    GeVtx(0x800, -0x800, 0);
    GeTexCoord(u, scale.y);
    GeVtx(-0x800, -0x800, 0);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
