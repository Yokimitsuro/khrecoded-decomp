#include "nitro/types.h"

typedef struct {
    int elapsed;
    s16 remainder;
    u16 duration;
} StepTimer;

int AdvanceTimerWithCarry(StepTimer *timer, int step, int amount)
{
    int result = 0;
    timer->elapsed += step;
    if (timer->elapsed >= (timer->duration << 12)) {
        amount += timer->remainder;
        timer->elapsed = 0;
        result = amount >> 12;
        timer->remainder = amount & 0xfff;
    }
    return result;
}
