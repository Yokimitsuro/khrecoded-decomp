#include "nitro/types.h"

extern int abs(int value);

u32 SnapAngleTowardQuadrant(int current, u32 angle, BOOL reverse)
{
    int step = 0x2000;
    int diff;
    int quarter;

    if (reverse) {
        step = -0x2000;
    }
    if ((int)(angle - current) < 0) {
        angle += step;
    } else {
        angle -= step;
    }
    angle = (u16)angle;
    diff = angle - current;
    if (diff < 0) {
        quarter = -0x4000;
    } else {
        quarter = 0x4000;
    }
    while (abs(diff) > abs(diff - quarter)) {
        diff -= quarter;
        angle -= quarter;
    }
    angle = (u16)angle;
    if (!reverse && abs(angle - current) >= 0x4000) {
        angle = 0x10000 - angle;
    }
    return angle;
}
