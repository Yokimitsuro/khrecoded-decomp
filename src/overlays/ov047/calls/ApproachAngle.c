#include "nitro/types.h"

extern int FX_Mul(int left, int right);

u16 ApproachAngle(int from, int to)
{
    int diff = (u16)(to - from);
    int step;

    if (diff >= 0x8000) {
        diff -= 0x10000;
    }
    if (diff > 0) {
        step = FX_Mul(diff, 0x2ac) + 0x400;
        if (step <= diff) {
            if (step < 0) {
                step = 0;
            }
            diff = step;
        }
    } else {
        step = FX_Mul(diff, 0x2ac) - 0x400;
        if (step > 0) {
            diff = 0;
        } else if (step >= diff) {
            diff = step;
        }
    }
    return from + diff;
}
