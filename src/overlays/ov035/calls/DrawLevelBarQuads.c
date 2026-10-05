#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void SetupMovieCamera(void);
extern int func_02028c38(const VecFx32 *pWorld, int *px, int *py);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);

static inline void GeomBegin(u32 primitive) {
    u32 arg = primitive;
    NNS_G3dGeBufferOP_N(0x40, &arg, 1);
}

static inline void GeomColor(u32 color) {
    u32 arg = color;
    NNS_G3dGeBufferOP_N(0x20, &arg, 1);
}

static inline void GeomVtx(fx16 x, fx16 y, fx16 z) {
    u32 args[2];
    args[0] = (u32)(u16)x | ((u32)(u16)y << 16);
    args[1] = (u32)(u16)z;
    NNS_G3dGeBufferOP_N(0x23, args, 2);
}

static inline void GeomEnd(void) {
    NNS_G3dGeBufferOP_N(0x41, NULL, 0);
}

void DrawLevelBarQuads(void *work, const VecFx32 *position, u16 levelA, u16 levelB, u16 scale) {
    int x;
    int y;
    int top;

    SetupMovieCamera();
    func_02028c38(position, &x, &y);
    x -= scale / 2;
    y = 0xb6 - y;
    top = y - 4;
    if (levelA != 0) {
        GeomBegin(1);
        GeomColor(0x27f4);
        GeomVtx(x + levelA, y, 0x2000);
        GeomVtx(x, y, 0x2000);
        GeomColor(0x1e2);
        GeomVtx(x, top, 0x2000);
        GeomVtx(x + levelA, top, 0x2000);
        GeomEnd();
    }
    if (levelB < scale) {
        GeomBegin(1);
        GeomColor(0x2108);
        GeomVtx(x + scale, y, 0x1000);
        GeomVtx(x + levelB, y, 0x1000);
        GeomVtx(x + levelB, top, 0x1000);
        GeomVtx(x + scale, top, 0x1000);
        GeomEnd();
    }
    if (levelA < levelB) {
        GeomBegin(1);
        GeomColor(0x1f);
        GeomVtx(x + levelB, y, 0);
        GeomVtx(x + levelA, y, 0);
        GeomVtx(x + levelA, top, 0);
        GeomVtx(x + levelB, top, 0);
    }
    GeomEnd();
}
