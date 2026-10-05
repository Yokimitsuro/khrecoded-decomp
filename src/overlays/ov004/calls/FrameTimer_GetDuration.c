#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

u16 FrameTimer_GetDuration(FrameTimer *timer)
{
    return timer->endFrame - timer->startFrame;
}
