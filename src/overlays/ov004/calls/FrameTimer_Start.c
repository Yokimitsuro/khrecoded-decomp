#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 data_ov004_020645a0;

void FrameTimer_Start(FrameTimer *timer, u16 duration)
{
    timer->startFrame = data_ov004_020645a0;
    timer->endFrame = data_ov004_020645a0 + duration;
}
