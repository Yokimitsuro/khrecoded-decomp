#include "nitro/types.h"
#include "nitro/fx_types.h"

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

void DrawTexturedQuad(fx32 left, fx32 top, fx32 right, fx32 bottom, fx16 x0, fx16 y0, fx16 x1, fx16 y1)
{
    GeCommand1(0x40, 1);
    GeTexCoord(left, top);
    GeVtx(x0, y0, 0);
    GeTexCoord(right, top);
    GeVtx(x1, y0, 0);
    GeTexCoord(right, bottom);
    GeVtx(x1, y1, 0);
    GeTexCoord(left, bottom);
    GeVtx(x0, y1, 0);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
