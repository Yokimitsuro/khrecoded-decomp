#include "nitro/types.h"

typedef struct CounterGoal {
    void *handler;
    u8 pad_04[0xc];
    s8 reached;
    u8 pad_11[3];
    u32 goal;
    s8 index;
    s8 source;
} CounterGoal;

extern u32 func_ov001_02068e8c(void);
extern u32 func_ov001_02068ea4(s32 index);
extern u32 func_ov001_02068e80(void);
extern u32 GetClampedTimerValue(void);
extern void func_ov001_02069434(void);

int EventTrigger_CheckCounterGoal(CounterGoal *counter)
{
    BOOL countsDown = FALSE;
    u32 goal;
    u32 value;

    counter->reached = 0;
    goal = counter->goal;
    switch (counter->source) {
    case 0:
        value = func_ov001_02068e8c();
        break;
    case 1:
        value = func_ov001_02068ea4(counter->index);
        break;
    case 2:
        value = func_ov001_02068e80();
        break;
    case 3:
        value = GetClampedTimerValue();
        break;
    case 4:
        value = GetClampedTimerValue();
        countsDown = TRUE;
        break;
    }
    if (!countsDown) {
        if (goal == 0) {
            counter->reached = 1;
        } else if (value != 0 && goal <= value) {
            counter->reached = 1;
        }
    } else if (value <= goal) {
        counter->reached = 1;
    }
    if (counter->reached) {
        counter->handler = (void *)func_ov001_02069434;
    }
    return counter->reached;
}
