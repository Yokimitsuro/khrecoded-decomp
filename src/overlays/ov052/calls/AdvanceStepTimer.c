#include "nitro/types.h"

typedef struct {
    int elapsed;
    u16 count;
    u16 duration;
} StepTimer;

int AdvanceStepTimer(StepTimer *timer, int step, int value)
{
    int result = 0;
    timer->elapsed += step;
    if (timer->elapsed >= (timer->duration << 12)) {
        result = value;
        timer->count = 0;
        timer->elapsed = 0;
    }
    return result;
}
