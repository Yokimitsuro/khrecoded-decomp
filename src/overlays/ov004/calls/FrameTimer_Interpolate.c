#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 data_ov004_020645a0;
extern u32 _u32_div_f(u32 dividend, u32 divisor);

u16 FrameTimer_Interpolate(FrameTimer *timer, u16 value)
{
    if (timer->endFrame <= data_ov004_020645a0) {
        return value;
    }
    return _u32_div_f(value * (data_ov004_020645a0 - timer->startFrame), timer->endFrame - timer->startFrame);
}
