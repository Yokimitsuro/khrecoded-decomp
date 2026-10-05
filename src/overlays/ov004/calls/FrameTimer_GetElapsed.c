#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 data_ov004_020645a0;

u16 FrameTimer_GetElapsed(FrameTimer *timer)
{
    if (data_ov004_020645a0 >= timer->endFrame) {
        return timer->endFrame - timer->startFrame;
    }
    return data_ov004_020645a0 - timer->startFrame;
}
