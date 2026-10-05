#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

#define reg_G3_TEXCOORD       (*(REGType32v *)0x04000488)
#define reg_G3_VTX_16         (*(REGType32v *)0x0400048c)
#define reg_G3_VTX_XY         (*(REGType32v *)0x04000494)
#define reg_G3_POLYGON_ATTR   (*(REGType32v *)0x040004a4)
#define reg_G3_TEXIMAGE_PARAM (*(REGType32v *)0x040004a8)
#define reg_G3_TEXPLTT_BASE   (*(REGType32v *)0x040004ac)
#define reg_G3_BEGIN_VTXS     (*(REGType32v *)0x04000500)
#define reg_G3_END_VTXS       (*(REGType32v *)0x04000504)

#define GX_FX16PAIR(a, b) ((u32)(((u32)(u16)(a)) | ((u32)(u16)(b) << 16)))
#define GX_BEGIN_QUADS 1
#define GX_CULL_NONE 3

static inline void G3_Vtx(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_16 = GX_FX16PAIR(x, y);
    reg_G3_VTX_16 = (u32)(u16)z;
}

static inline void G3_VtxXY(fx16 x, fx16 y)
{
    reg_G3_VTX_XY = GX_FX16PAIR(x, y);
}

static inline void G3_TexCoordPx(int s, int t)
{
    reg_G3_TEXCOORD = ((u32)s << 4) | ((u32)t << 20);
}

typedef struct SpriteTexture {
    u32 texImageParam;
    u32 paletteBase;
} SpriteTexture;

typedef struct Billboard {
    struct Billboard *next;
    u32 unk_04;
    const SpriteTexture *texture;
    VecFx32 position;
    s16 width;
    fx16 height;
    u8 s0;
    u8 t0;
    u8 s1;
    u8 t1;
    s16 alpha;
    s16 polygonId;
} Billboard;

extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern MtxFx43 data_02056020;
extern void MTX_MultVec43(const VecFx32 *vec, const MtxFx43 *m, VecFx32 *dst);
extern void G3_LoadMtx43(const MtxFx43 *m);

void Billboard_DrawList(Billboard **list)
{
    Billboard *node;

    for (node = *list; node != NULL; node = node->next) {
        fx16 halfWidth = (fx16)(node->width / 2);

        if (node->alpha > 0) {
            reg_G3_TEXIMAGE_PARAM = node->texture->texImageParam;
            reg_G3_TEXPLTT_BASE = node->texture->paletteBase;
            MTX_MultVec43(&node->position, &NNS_G3dGlb_cameraMtx, (VecFx32 *)((u8 *)&data_02056020 + 0x24));
            G3_LoadMtx43(&data_02056020);
            reg_G3_POLYGON_ATTR = (node->alpha << 16) | ((node->polygonId << 24) | (GX_CULL_NONE << 6));
            reg_G3_BEGIN_VTXS = GX_BEGIN_QUADS;
            G3_TexCoordPx(node->s0, node->t0);
            G3_Vtx(-halfWidth, node->height, 0);
            G3_TexCoordPx(node->s0, node->t1);
            G3_VtxXY(-halfWidth, 0);
            G3_TexCoordPx(node->s1, node->t1);
            G3_VtxXY(halfWidth, 0);
            G3_TexCoordPx(node->s1, node->t0);
            G3_VtxXY(halfWidth, node->height);
            reg_G3_END_VTXS = 0;
        }
    }
}
