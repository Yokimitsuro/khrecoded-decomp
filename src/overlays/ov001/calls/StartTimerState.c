#include "nitro/types.h"

typedef struct TimerWork {
    u8 pad_00[0x24];
    u8 enabled;
    u8 pad_25[3];
    u32 startMilliseconds;
} TimerWork;

extern TimerWork *NNSi_FndGetCurrentRootHeap(void);
extern u64 OS_GetTick(void);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern void *func_ov001_02068c88(void);

void *StartTimerState(void)
{
    TimerWork *work = NNSi_FndGetCurrentRootHeap();

    if (!work->enabled) {
        return NULL;
    }
    work->startMilliseconds = _ll_udiv(OS_GetTick() * 64, 0x82ea);
    return func_ov001_02068c88;
}
