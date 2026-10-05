#include "nitro/types.h"

extern const s16 data_02053580[];

u16 Math_AcosIdx(int cosine)
{
    int low;
    int high;
    int middle;
    s16 target;

    if (cosine >= 0) {
        low = 0;
        high = 0x400;
    } else {
        low = 0x400;
        high = 0x800;
    }
    target = (s16)cosine;

    while (low <= high) {
        middle = (low + high) / 2;
        if (target == data_02053580[(0x400 - middle) & 0xfff]) {
            break;
        }
        if (data_02053580[(0x400 - middle) & 0xfff] < target) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return (u16)(((middle * 2 + 1) << 16) / 0x2000);
}
