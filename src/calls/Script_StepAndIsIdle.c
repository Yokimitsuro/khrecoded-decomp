#pragma thumb on
extern void func_0204d164(void);
extern int IsSceneState1(void);

enum { SCHED_BUSY = 0, SCHED_IDLE = 1 };

int Script_StepAndIsIdle(void)
{
    func_0204d164();
    return IsSceneState1() != 0 ? SCHED_BUSY : SCHED_IDLE;
}
