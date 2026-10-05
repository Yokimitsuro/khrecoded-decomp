#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

extern u32 data_ov004_020645a0;

BOOL FrameTimer_IsExpired(FrameTimer *timer)
{
    return data_ov004_020645a0 >= timer->endFrame;
}
