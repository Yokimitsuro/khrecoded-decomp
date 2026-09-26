#pragma thumb on
extern void func_0204d164(void);
extern int func_0204d6ec(void);

enum { SCHED_BUSY = 0, SCHED_IDLE = 1 };

int func_0202673c(void)
{
    func_0204d164();
    return func_0204d6ec() != 0 ? SCHED_BUSY : SCHED_IDLE;
}
