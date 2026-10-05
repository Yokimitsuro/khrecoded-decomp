#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void GeCommand1(u32 op, u32 param)
{
    u32 data[1];
    data[0] = param;
    NNS_G3dGeBufferOP_N(op, data, 1);
}

static inline void GeVtx(fx16 x, fx16 y, fx16 z)
{
    u32 data[2];
    data[0] = (u16)x | ((u16)y << 16);
    data[1] = (u16)z;
    NNS_G3dGeBufferOP_N(0x23, data, 2);
}

void DrawGradientRect(int left, int top, int right, u16 bottom, fx16 depth, u16 topColor, u16 bottomColor)
{
    int z = depth;

    GeCommand1(0x40, 1);
    GeCommand1(0x20, topColor);
    GeVtx(right, (u16)(0xbf - top), z);
    GeVtx(left, (u16)(0xbf - top), z);
    GeCommand1(0x20, bottomColor);
    GeVtx(left, (u16)(0xbf - bottom), z);
    GeVtx(right, (u16)(0xbf - bottom), z);
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}
