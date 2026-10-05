#include "nitro/types.h"

typedef struct TimerTask TimerTask;

struct TimerTask {
    void (*update)(TimerTask *task);
    u32 unk_04;
    u32 unk_08;
    u32 duration;
    s8 result;
    s8 timerSlot;
};

extern u32 func_ov001_02068eb4(int slot);
extern void func_ov001_02068e18(int slot);
extern void func_ov001_02069434(TimerTask *task);

int PollTimerTask(TimerTask *task)
{
    u32 elapsed = func_ov001_02068eb4(task->timerSlot);

    if (elapsed != 0 && elapsed >= task->duration) {
        func_ov001_02068e18(task->timerSlot);
        task->update = func_ov001_02069434;
        task->timerSlot = -1;
        return task->result;
    }
    return 0;
}
