#include "nitro/types.h"

extern int FX_Mul(int a, int b);

void ComputePulseScaleColor(int phase, int *scale, u16 *color) {
    int wave;
    u16 level;
    int masked = phase & 0xfff;

    switch (masked >> 10) {
    case 0:
        wave = (masked * 4) & 0xfff;
        break;
    case 1:
    case 2:
        wave = 0xfff - (((masked + 0x400) * 2) & 0xfff);
        break;
    default:
        wave = 0;
        break;
    }
    *scale = FX_Mul(wave, 0x2aa) + 0x1000;
    level = (u16)(wave >> 7);
    *color = 0x1f | (level << 5) | (level << 10);
}
