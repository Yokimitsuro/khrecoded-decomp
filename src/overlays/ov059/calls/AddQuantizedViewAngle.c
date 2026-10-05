#include "nitro/types.h"

extern int GetCameraRollAngle(void);
extern s32 _s32_div_f(s32 numerator, s32 denominator);

u16 AddQuantizedViewAngle(u16 angle)
{
    int viewAngle = (s16)GetCameraRollAngle();
    s8 sign = (viewAngle == 0) ? 0 : ((viewAngle > 0) ? 1 : -1);
    int magnitude = viewAngle;

    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude < 0x3fff) {
        return angle + (u16)(_s32_div_f(sign * (magnitude + 0x80), 0x1fff) * 0x1fff);
    }
    return angle + (u16)(_s32_div_f(sign * (magnitude + 0x107f), 0x1fff) * 0x1fff);
}
