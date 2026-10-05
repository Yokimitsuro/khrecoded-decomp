#include "nitro/types.h"

typedef struct { s8 dx, dy; } Direction;

extern void NNSi_G2dTextCanvasDrawString(int *ctx, u32 x, u32 y, u32 p4, u32 flags, u32 p6, Direction dir);

void DrawDirectional(int self, u32 x, u32 y, u32 p4, u32 flags, u32 p6)
{
    int *p = *(int **)(self + 0x14);
    Direction dir = {0, 0};

    switch (*(u8 *)(*(int *)(*p + 8) + 7)) {
    case 0:
    case 7:
        dir.dx = 1;
        break;
    case 1:
    case 2:
        dir.dy = 1;
        break;
    case 3:
    case 4:
        dir.dx = -1;
        break;
    case 5:
    case 6:
        dir.dy = -1;
        break;
    }
    NNSi_G2dTextCanvasDrawString((int *)(self + 0x10), x, y, p4, flags, p6, dir);
}
