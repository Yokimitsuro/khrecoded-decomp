#include "nitro/types.h"

typedef struct { s8 dx, dy; } TextDir;

extern u8 *data_ov002_0206c460;
extern void NNSi_G2dTextCanvasDrawTextRect(int *ctx, int p2, int p3, int p4, int p5, int p6, int p7, int p8, TextDir dir);

void DrawPanelSlotABText(int param1, int p2, int p3, int p4, int p5, int p6, int p7, int p8) {
    int newFlags;
    int self;
    int *fontChain;

    if (param1 == 0) {
        newFlags = data_ov002_0206c460[0x10] | 0x40;
        self = (int)data_ov002_0206c460 + 0x48;
    } else {
        newFlags = data_ov002_0206c460[0x10] | 0x80;
        self = (int)data_ov002_0206c460 + 0x7c;
    }
    data_ov002_0206c460[0x10] = newFlags;

    TextDir dir = {0, 0};
    fontChain = *(int **)(self + 0x14);
    switch (*(u8 *)(*(int *)(*fontChain + 8) + 7)) {
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
    NNSi_G2dTextCanvasDrawTextRect((int *)(self + 0x10), p2, p3, p4, p5, p6, p7, p8, dir);
}
